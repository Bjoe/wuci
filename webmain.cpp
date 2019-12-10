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

    navigationBar_ = rootContainer->addNew<Wt::WNavigationBar>();
    navigationBar_->setTitle("Easy Config", "http://startpage.com");
    navigationBar_->setResponsive(true);

    stackedWidget_ = rootContainer->addNew<Wt::WStackedWidget>();
    stackedWidget_->addStyleClass("contents");

    auto lm = std::make_unique<Wt::WMenu>(stackedWidget_);
    leftMenu_ = navigationBar_->addMenu(std::move(lm));
  }

  void WebMain::prepareVpnConfigPage()
  {
    //auto[widgetPage, instance] = VpnPage::create(maxWidth_);
    auto[widgetPage, instance] = VpnUploadPage::create(messageBus_, maxWidth_);
    vpnConfigPage_ = instance;

    //stackedWidget_->addWidget(std::move(widgetPage));
    leftMenu_->addItem("VPN", std::move(widgetPage));
  }

  void WebMain::prepareWlanConfigPage()
  {
    auto[widgetPage, instance] = WlanPage::create(messageBus_, maxWidth_);
    wlanConfigPage_ = instance;

    //Wt::WWidget* wc = stackedWidget_->addWidget<Wt::WWidget>(std::move(widgetPage));
    leftMenu_->addItem("WLAN", std::move(widgetPage));
/*    vpnConfigPage_->connect([this, wc]()
    {
      stackedWidget_->setCurrentWidget(wc);
    });



    // Done

    auto container = std::make_unique<Wt::WContainerWidget>();
    container->addNew<Wt::WText>("Done");
    Wt::WWidget* wi = stackedWidget_->addWidget<Wt::WWidget>(std::move(container));
    wlanConfigPage_->connect([this, wi]()
    {
        stackedWidget_->setCurrentWidget(wi);
    });*/
  }

} // namespace wuci
