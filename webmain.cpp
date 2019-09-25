#include "webmain.hpp"

namespace wuci {

  WebMain::WebMain(const Wt::WEnvironment &env) : Wt::WApplication(env)
  {
    setTitle("W-UCI");

    auto rootContainer = root();

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
