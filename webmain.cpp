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
    vpnConfigPage_.connect([this]()
    {
      stackedWidget_->setCurrentIndex(1);
    });
  }

  void WebMain::prepareWlanConfigPage()
  {
    stackedWidget_->addWidget(wlanConfigPage_.preparePage());
  }

} // namespace wuci
