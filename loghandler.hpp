#ifndef WUCI_LOGHANDLER_H
#define WUCI_LOGHANDLER_H

extern "C" {
#include <libubus.h>
};

#include <string>
#include <deque>

namespace wuci {

class LogHandler
{
public:
    LogHandler(struct ubus_request* req);

    std::deque<std::string> getMessages() const;
};

} // namespace wuci

#endif // WUCI_LOGHANDLER_H
