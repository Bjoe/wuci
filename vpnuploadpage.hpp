#ifndef WUCI_VPNUPLOADPAGE_HPP
#define WUCI_VPNUPLOADPAGE_HPP

#include <memory>
#include <functional>
#include <tuple>
#include <optional>

#include <Wt/WWidget.h>
#include <Wt/WLength.h>

#include "messagebus.hpp"

namespace Wt {
    class WPushButton;
    class WText;
}

namespace wuci {

class VpnUploadPage
{
public:
    static std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<VpnUploadPage>> create(std::optional<MessageBus> msgBus,
                                                                                         Wt::WLength maxWidth);

    void connect(std::function<void()> callback);

private:
    static constexpr const char* OPENVPN_CONFIG_FILE_ = {"/etc/openvpn/my-vpn.conf"};

    VpnUploadPage(Wt::WPushButton* okButton, Wt::WText* state);

    Wt::WPushButton* okButton_;
    Wt::WText* state_;
};

} // namespace wuci

#endif // WUCI_VPNUPLOADPAGE_HPP
