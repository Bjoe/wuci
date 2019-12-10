#include "wlanconfig.hpp"

#include <vector>
#include <cstdlib>
#include <cstring>
#include <uci.h>
#include <functional>

namespace wuci {

namespace {

std::variant<std::string, ErrorCode> getUciValue(uci_context* ctx, const char* config)
{
    std::size_t l = std::strlen(config);
    char* c = new char[l + 1]();
    std::strncpy(c, config, l);

    uci_ptr ptr;
    int ret = uci_lookup_ptr(ctx, &ptr, c, true);

    uci_element *e = ptr.last;

    std::variant<std::string, ErrorCode> returnValue = {};
    if(ret == UCI_OK &&
            e->type == UCI_TYPE_OPTION &&
            ptr.o->type == UCI_TYPE_STRING)
    {
        returnValue = ptr.o->v.string;
        uci_unload(ctx, ptr.p);
    }
    else
    {
        if(ret != UCI_OK)
        {
            char* errorStr = {};
            uci_get_errorstr(ctx, &errorStr, config);
            std::string err = {errorStr};
            std::free(errorStr);

            ErrorCode error{err};
            returnValue = error;

            // Unload ptr.p ??? uci_unload(ctx_, ptr.p);
        }
        else
        {
            // TODO Improve error output
            //     if(e->type == UCI_TYPE_OPTION && ptr.o->type == UCI_TYPE_STRING)
            //{
            //    std::cout << "\n\n" << ptr.o->section->package->e.name << "." << ptr.o->section->e.name << "." << ptr.o->e.name << "=" << ptr.o->v.string << std::endl;
            //}

            ErrorCode error{"Wrong uci type"};
            returnValue = error;
            uci_unload(ctx, ptr.p);
        }
    }

    return returnValue;
}

[[nodiscard]] ErrorCode setUciValue(uci_context* ctx, std::string&& value)
{
    ErrorCode returnValue = {};
    auto verify = [returnValue, ctx, value](std::function<int()> callback, std::string str) -> ErrorCode
    {
        if(returnValue.state() == ErrorCode::OK && callback() != UCI_OK)
        {
            str.append(": ");
            str.append(value.c_str());
            char* errorStr = {};
            uci_get_errorstr(ctx, &errorStr, str.c_str());
            std::string err = {errorStr};
            std::free(errorStr);

            ErrorCode error{err};
            return error;
        }
        return returnValue;
    };

    std::vector<char> c(value.c_str(), value.c_str() + value.size() + 1);
    uci_ptr ptr;

    verify([ctx, &ptr, &c](){ return uci_lookup_ptr(ctx, &ptr, &c[0], true);}, "UCI lookup");

    uci_element *e = ptr.last;

    if((e && e->type == UCI_TYPE_OPTION && ptr.o->type == UCI_TYPE_STRING) ||
            (ptr.o == nullptr && not std::string(ptr.option).empty()))
    {
        verify([ctx, &ptr](){ return uci_set(ctx, &ptr); }, "UCI set");
        verify([ctx, &ptr](){ return uci_save(ctx, ptr.p);}, "UCI save");

        std::string k = {""};
        k.append(value);
        std::vector<char> commit(k.c_str(), k.c_str() + k.size() + 1);
        verify([ctx, &ptr, &commit](){ return uci_lookup_ptr(ctx, &ptr, &commit[0], true);}, "UCI commit lookup");
        verify([ctx, &ptr](){ return uci_commit(ctx, &ptr.p, false); }, "UCI commit");
        uci_unload(ctx, ptr.p);
    }
    else
    {
        // TODO Improve error output
        // if(e->type != UCI_TYPE_OPTION)
        // {}
        // if(ptr.o->type != UCI_TYPE_STRING)
        // {
        //    std::cout << "\n\n" << ptr.o->section->package->e.name << "." << ptr.o->section->e.name << "." << ptr.o->e.name << "=" << ptr.o->v.string << std::endl;
        // }

        ErrorCode error{"Cannot set uci type: " + value};
        returnValue = error;
        uci_unload(ctx, ptr.p);
    }

    return returnValue;
}
}

std::optional<WlanConfig> WlanConfig::create()
{
    uci_context* ctx = uci_alloc_context();
    if(!ctx)
    {
        return {};
    }

    std::shared_ptr<uci_context> c = {ctx, uci_free_context};
    return WlanConfig(c);
}

std::variant<std::string, ErrorCode> WlanConfig::ssid() const
{
    auto* ssid =  SSID_;
    return getUciValue(ctx_.get(), ssid);
}

std::variant<std::string, ErrorCode> WlanConfig::key() const
{
    auto* key = KEY_;
    return getUciValue(ctx_.get(), key);
}

std::variant<std::string, ErrorCode> WlanConfig::encryption() const
{
    auto* enc = ENCRYPTION_;
    return getUciValue(ctx_.get(), enc);
}

ErrorCode WlanConfig::setSsid(std::string&& ssid)
{
    std::string value{SSID_};
    value.append("=");
    value.append(ssid);
    return setUciValue(ctx_.get(), std::move(value));
}

ErrorCode WlanConfig::setKey(std::string&& key)
{
    std::string value{KEY_};
    value.append("=");
    value.append(key);
    return setUciValue(ctx_.get(), std::move(value));
}

ErrorCode WlanConfig::setEncryption(std::string &&enc)
{
    std::string value{ENCRYPTION_};
    value.append("=");
    value.append(enc);
    return setUciValue(ctx_.get(), std::move(value));
}

WlanConfig::WlanConfig(std::shared_ptr<uci_context> ctx) : ctx_(ctx)
{}

} // namespace wuci
