extern "C" {
#include <libubus.h>
#include <libubox/uloop.h>
#include <libubox/ustream.h>
#include <libubox/blob.h>
#include <libubox/blobmsg.h>
#include <libubox/blobmsg_json.h>
#define SYSLOG_NAMES
#include <syslog.h>
};

#include <cstdint>
#include <ctime>

#include "loghandler.hpp"

namespace wuci {

namespace  {

enum {
    LOG_STDOUT,
    LOG_FILE,
    LOG_NET,
};

enum {
    LOG_MSG,
    LOG_ID,
    LOG_PRIO,
    LOG_SOURCE,
    LOG_TIME,
    __LOG_MAX
};

const struct blobmsg_policy log_policy[] = {
    [LOG_MSG] = { .name = "msg", .type = BLOBMSG_TYPE_STRING },
    [LOG_ID] = { .name = "id", .type = BLOBMSG_TYPE_INT32 },
    [LOG_PRIO] = { .name = "priority", .type = BLOBMSG_TYPE_INT32 },
    [LOG_SOURCE] = { .name = "source", .type = BLOBMSG_TYPE_INT32 },
    [LOG_TIME] = { .name = "time", .type = BLOBMSG_TYPE_INT64 },
};

static std::deque<std::string> logMessagesQueue{};

std::string getcodetext(int value, CODE *codetable) {
    CODE *i;

    if (value >= 0)
        for (i = codetable; i->c_val != -1; i++)
            if (i->c_val == value)
                return (i->c_name);
    return "<unknown>";
};

void notifyRead(struct ustream *s, int /*bytes*/)
{
    while (true) {

        int len;
        void* b = ustream_get_read_buf(s, &len);
        struct blob_attr *msg = static_cast<blob_attr*>(b);
        if (static_cast<std::size_t>(len) < sizeof(*msg))
            break;

        std::size_t cur_len = blob_len(msg) + sizeof(*msg);
        if (static_cast<std::size_t>(len) < cur_len)
            break;

        struct blob_attr *tb[__LOG_MAX];
        blobmsg_parse(log_policy, ARRAY_SIZE(log_policy), tb, blob_data(msg), blob_len(msg));
        std::string message(blobmsg_get_string(tb[LOG_MSG]));
         if(message.find("openvpn") == std::string::npos)
            continue;

        std::uint32_t p = blobmsg_get_u32(tb[LOG_PRIO]);
        std::string name = getcodetext(LOG_FAC(p) << 3, facilitynames);
        std::string prio = getcodetext(LOG_PRI(p), prioritynames);

        std::time_t t = blobmsg_get_u64(tb[LOG_TIME]) / 1000;
        std::string time(std::ctime(&t));

        logMessagesQueue.emplace_back("" + time + " " + name + "." + prio + ""
                                        + ((blobmsg_get_u32(tb[LOG_SOURCE])) ? (" ") : (" kernel:"))
                                        + message + "");

        ustream_consume(s, cur_len);
    }
}

void ubusFdHandler(ubus_request */*req*/, int fd)
{
    static struct ustream_fd test_fd{};
    memset(&test_fd, 0, sizeof(test_fd));

    test_fd.stream.notify_read = notifyRead;
    test_fd.stream.notify_state = [](struct ustream */*s*/)
    {
        uloop_end();
    };

    ustream_fd_init(&test_fd, fd);
}

}

LogHandler::LogHandler(struct ubus_request* req)
{
    req->fd_cb = ubusFdHandler;
}

std::deque<std::string> LogHandler::getMessages() const
{
    std::deque<std::string> l{};
    logMessagesQueue.swap(l);
    return l;
}

} // namespace wuci
