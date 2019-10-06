#include "wlanconfig.hpp"

#include <vector>
#include <cstdlib>
#include <cstring>
#include <uci.h>

namespace wuci {

namespace {

std::variant<std::string, Error> getUciValue(uci_context* ctx, const char* config)
{
    std::size_t l = std::strlen(config);
    char* c = new char[l + 1]();
    std::strncpy(c, config, l);

    uci_ptr ptr;
    int ret = uci_lookup_ptr(ctx, &ptr, c, true);

    uci_element *e = ptr.last;

    std::variant<std::string, Error> returnValue = {};
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

            Error error{err};
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

            Error error{"Wrong uci type"};
            returnValue = error;
            uci_unload(ctx, ptr.p);
        }
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

std::variant<std::string, Error> WlanConfig::ssid() const
{
    auto* ssid =  SSID_;
    return getUciValue(ctx_.get(), ssid);
}

std::variant<std::string, Error> WlanConfig::key() const
{
    auto* key = KEY_;
    return getUciValue(ctx_.get(), key);
}

WlanConfig::WlanConfig(std::shared_ptr<uci_context> ctx) : ctx_(ctx)
{}

} // namespace wuci
