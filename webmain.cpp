#include "webmain.hpp"

#include <Wt/WStackedWidget.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WBootstrapTheme.h>

namespace wuci {

  WebMain::WebMain(const Wt::WEnvironment &env) : Wt::WApplication(env)
  {
    auto theme = std::make_shared<Wt::WBootstrapTheme>();
    theme->setVersion(Wt::BootstrapVersion::v3);

    setTheme(theme);

    setTitle("W-UCI");

    auto rootContainer = root();

    navigationBar_ = rootContainer->addNew<Wt::WNavigationBar>();

    stackedWidget_ = rootContainer->addNew<Wt::WStackedWidget>();
  }

  void WebMain::prepareVpnConfigPage()
  {
    auto[widgetPage, instance] = VpnConfig::createPage(maxWidth_);
    vpnConfigPage_ = instance;
    stackedWidget_->addWidget(std::move(widgetPage));
  }

  void WebMain::prepareWlanConfigPage()
  {
    auto[widgetPage, instance] = WlanConfig::createPage(maxWidth_);
    wlanConfigPage_ = instance;

    Wt::WWidget* wc = stackedWidget_->addWidget<Wt::WWidget>(std::move(widgetPage));
    vpnConfigPage_->connect([this, wc]()
    {
      stackedWidget_->setCurrentWidget(wc);
    });
  }

} // namespace wuci
