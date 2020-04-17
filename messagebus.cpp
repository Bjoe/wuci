extern "C" {
#include <libubus.h>
#include <libubox/uloop.h>
#include <libubox/ustream.h>
#include <libubox/blob.h>
#include <libubox/blobmsg.h>
#include <libubox/blobmsg_json.h>
};

#include <cstdint>
#include <ctime>
#include <regex.h>
#include "messagebus.hpp"

namespace wuci {

std::optional<MessageBus> MessageBus::create()
{
     uloop_init(); // TODO(Bjoe) Needs a taskrunner
     struct ubus_context *ctx = ubus_connect(nullptr);
     if(!ctx)
         return {};
     ubus_add_uloop(ctx);
     std::shared_ptr<ubus_context> c = {ctx, ubus_free};
     return MessageBus(c);
}

std::optional<LogHandler> MessageBus::readLog() const
{
    std::uint32_t objId{};
    static struct blob_buf buf{};
    blob_buf_init(&buf, 0);
    blobmsg_add_u8(&buf, "stream", 1);
    blobmsg_add_u8(&buf, "oneshot", 1);
    blobmsg_add_u32(&buf, "lines", 10);

    if(ubus_lookup_id(ubusCtx_.get(), "log", &objId))
        return {};

    struct ubus_request req{};
    if(ubus_invoke_async(ubusCtx_.get(), objId, "read", buf.head, &req))
        return {};

    LogHandler lgh(&req);
    ubus_complete_request_async(ubusCtx_.get(), &req);
    uloop_run(); // TODO(Bjoe) Needs a taskrunner
    return lgh;
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

void MessageBus::restartSystem() const
{
    std::uint32_t objId{};
    ubus_lookup_id(ubusCtx_.get(), "system", &objId);

    blob_buf buf{};
    blob_buf_init(&buf, 0);
    ubus_invoke(ubusCtx_.get(), objId, "reboot", buf.head, nullptr, nullptr, 3000);
}

MessageBus::MessageBus(std::shared_ptr<ubus_context> ubusCtx) : ubusCtx_(std::move(ubusCtx))
{

}

} // namespace wuci
