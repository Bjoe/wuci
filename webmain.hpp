#ifndef WUCI_WEBMAIN_HPP
#define WUCI_WEBMAIN_HPP

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLength.h>
#include <memory>
#include <optional>

#include "vpnpage.hpp"
#include "vpnuploadpage.hpp"
#include "wlanpage.hpp"
#include "messagebus.hpp"

namespace Wt {
    class WStackedWidget;
    class WNavigationBar;
    class WMenu;
}

namespace wuci {

    class WebMain : public Wt::WApplication
    {
    public:
        WebMain(const Wt::WEnvironment& env);

        void prepareVpnConfigPage();
        void prepareWlanConfigPage();

    private:
        Wt::WStackedWidget* stackedWidget_ = {};
        Wt::WNavigationBar* navigationBar_ = {};
        Wt::WMenu* leftMenu_ = {};

        Wt::WLength maxWidth_ = {500};
        //std::optional<VpnPage> vpnConfigPage_ = {};
        std::optional<VpnUploadPage> vpnConfigPage_ = {};
        std::optional<WlanPage> wlanConfigPage_ = {};
        std::optional<MessageBus> messageBus_ = MessageBus::create();
    };

} // namespace wuci

#endif // WUCI_WEBMAIN_HPP
