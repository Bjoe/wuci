#ifndef WUCI_WEBMAIN_HPP
#define WUCI_WEBMAIN_HPP

#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WNavigationBar.h>
#include <memory>

#include "vpnconfig.hpp"
#include "wlanconfig.hpp"

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

        VpnConfig vpnConfigPage_ = {};
        WlanConfig wlanConfigPage_ = {};
    };

} // namespace wuci

#endif // WUCI_WEBMAIN_HPP
