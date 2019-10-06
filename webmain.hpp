#ifndef WUCI_WEBMAIN_HPP
#define WUCI_WEBMAIN_HPP

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WLength.h>
#include <memory>
#include <optional>

#include "vpnpage.hpp"
#include "wlanpage.hpp"

namespace Wt {
    class WStackedWidget;
    class WToolBar;
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
        Wt::WToolBar* toolBar_ = {};

        Wt::WLength maxWidth_ = {500};
        std::optional<VpnPage> vpnConfigPage_ = {};
        std::optional<WlanPage> wlanConfigPage_ = {};
    };

} // namespace wuci

#endif // WUCI_WEBMAIN_HPP
