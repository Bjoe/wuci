#ifndef WUCI_WLANCONFIG_H
#define WUCI_WLANCONFIG_H

#include <string>
#include <optional>
#include <variant>
#include <memory>

#include "error.hpp"

class uci_context;

namespace wuci {

class WlanConfig
{
public:
    static std::optional<WlanConfig> create();
    ~WlanConfig() = default;

    std::variant<std::string, Error> ssid() const;
    std::variant<std::string, Error> key() const;

private:
    static constexpr const char* SSID_ = {"wireless.@wifi-iface[-1].ssid"};
    static constexpr const char* KEY_ = {"wireless.@wifi-iface[-1].key"};

    WlanConfig(std::shared_ptr<uci_context> ctx);
    std::shared_ptr<uci_context> ctx_ = {};
};

} // namespace wuci

#endif // WUCI_WLANCONFIG_H
