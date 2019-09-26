#ifndef WUCI_WEBMAIN_HPP
#define WUCI_WEBMAIN_HPP

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLength.h>
#include <memory>
#include <optional>

#include "vpnconfig.hpp"
#include "wlanconfig.hpp"

namespace Wt {
    class WStackedWidget;
    class WNavigationBar;
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

        Wt::WLength maxWidth_ = {500};
        std::optional<VpnConfig> vpnConfigPage_ = {};
        std::optional<WlanConfig> wlanConfigPage_ = {};
    };

} // namespace wuci

#endif // WUCI_WEBMAIN_HPP
