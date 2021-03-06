#ifndef WUCI_MESSAGEBUS_HPP
#define WUCI_MESSAGEBUS_HPP

#include <string>
#include <memory>
#include <optional>

#include "loghandler.hpp"

struct ubus_context;

namespace wuci {

class MessageBus
{
public:
    static std::optional<MessageBus> create();
    ~MessageBus() = default;

    std::optional<LogHandler> readLog() const;
    int restartProcess(std::string processName) const;
    int restartNetwork() const;
    void restartSystem() const;

private:
    MessageBus(std::shared_ptr<ubus_context> ubusCtx);
    std::shared_ptr<ubus_context> ubusCtx_ = {};
};

} // namespace wuci

#endif // WUCI_MESSAGEBUS_HPP
