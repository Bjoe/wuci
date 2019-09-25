#include "webmain.hpp"

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
    stackedWidget_->addWidget(vpnConfigPage_.preparePage());
  }

  void WebMain::prepareWlanConfigPage()
  {
    Wt::WWidget* wc = stackedWidget_->addWidget<Wt::WWidget>(wlanConfigPage_.preparePage());
    vpnConfigPage_.connect([this, wc]()
    {
      stackedWidget_->setCurrentWidget(wc);
    });
  }

} // namespace wuci
