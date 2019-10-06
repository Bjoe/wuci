#include "webmain.hpp"

#include <Wt/WStackedWidget.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WMenu.h>
#include <Wt/WToolBar.h>
#include <Wt/WPushButton.h>

namespace wuci {

  WebMain::WebMain(const Wt::WEnvironment &env) : Wt::WApplication(env)
  {
    auto theme = std::make_shared<Wt::WBootstrapTheme>();
    theme->setVersion(Wt::BootstrapVersion::v3);

    setTheme(theme);

    setTitle("W-UCI");

    auto rootContainer = root();

    rootContainer->addNew<Wt::WText>("Start ->>");

    toolBar_ = rootContainer->addNew<Wt::WToolBar>();
    auto vpnConfigButton = std::make_unique<Wt::WPushButton>("VPN config");
    vpnConfigButton->setChecked(true);
    toolBar_->addButton(std::move(vpnConfigButton), Wt::AlignmentFlag::Middle);
    auto wlanConfigButton = std::make_unique<Wt::WPushButton>("WLAN config");
    toolBar_->addButton(std::move(wlanConfigButton), Wt::AlignmentFlag::Middle);

    rootContainer->addNew<Wt::WText>(" >> Finish");

    stackedWidget_ = rootContainer->addNew<Wt::WStackedWidget>();
  }

  void WebMain::prepareVpnConfigPage()
  {
    auto[widgetPage, instance] = VpnPage::create(maxWidth_);
    vpnConfigPage_ = instance;
    stackedWidget_->addWidget(std::move(widgetPage));
  }

  void WebMain::prepareWlanConfigPage()
  {
    auto[widgetPage, instance] = WlanPage::create(maxWidth_);
    wlanConfigPage_ = instance;

    Wt::WWidget* wc = stackedWidget_->addWidget<Wt::WWidget>(std::move(widgetPage));
    vpnConfigPage_->connect([this, wc]()
    {
      stackedWidget_->setCurrentWidget(wc);
    });
  }

} // namespace wuci
