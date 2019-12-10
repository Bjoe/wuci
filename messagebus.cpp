extern "C" {
#include <libubus.h>
#include <libubox/blobmsg.h>
};

#include "messagebus.hpp"

namespace wuci {

std::optional<MessageBus> MessageBus::create()
{
     struct ubus_context *ctx = ubus_connect(nullptr);
     if(not ctx)
         return {};

     std::shared_ptr<ubus_context> c = {ctx, ubus_free};
     return MessageBus(c);
}

int MessageBus::restartProcess(std::string processName) const
{
    std::uint32_t objId{};
    ubus_lookup_id(ubusCtx_.get(), "service", &objId);

    blob_buf buf{};
    blob_buf_init(&buf, 0);
    blobmsg_add_string(&buf, "name", processName.c_str());
    return ubus_invoke(ubusCtx_.get(), objId, "signal", buf.head, nullptr, nullptr, 3000);
}

int MessageBus::restartNetwork() const
{
    std::uint32_t objId{};
    ubus_lookup_id(ubusCtx_.get(), "network", &objId);

    blob_buf buf{};
    blob_buf_init(&buf, 0);

    return ubus_invoke(ubusCtx_.get(), objId, "restart", buf.head, nullptr, nullptr, 3000);
}

MessageBus::MessageBus(std::shared_ptr<ubus_context> ubusCtx) : ubusCtx_(std::move(ubusCtx))
{

}

} // namespace wuci
