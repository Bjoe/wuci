#ifndef WUCI_WLANCONFIG_H
#define WUCI_WLANCONFIG_H

#include <string>
#include <optional>
#include <variant>
#include <memory>

#include "errorcode.hpp"

class uci_context;

namespace wuci {

class WlanConfig
{
public:
    static std::optional<WlanConfig> create();
    ~WlanConfig() = default;

    std::variant<std::string, ErrorCode> ssid() const;
    std::variant<std::string, ErrorCode> key() const;
    std::variant<std::string, ErrorCode> encryption() const;

    [[nodiscard]] ErrorCode setSsid(std::string &&ssid);
    [[nodiscard]] ErrorCode setKey(std::string &&key);
    [[nodiscard]] ErrorCode setEncryption(std::string &&enc);

private:
    static constexpr const char* SSID_ = {"wireless.@wifi-iface[-1].ssid"};
    static constexpr const char* ENCRYPTION_ = {"wireless.@wifi-iface[-1].encryption"};
    static constexpr const char* KEY_ = {"wireless.@wifi-iface[-1].key"};

    WlanConfig(std::shared_ptr<uci_context> ctx);
    std::shared_ptr<uci_context> ctx_ = {};
};

} // namespace wuci

#endif // WUCI_WLANCONFIG_H
