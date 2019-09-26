#include "wlanconfig.hpp"

#include <Wt/WPanel.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WPushButton.h>

namespace wuci {

  WlanConfig::WlanConfig()
  {
  }

  std::unique_ptr<Wt::WWidget> WlanConfig::preparePage()
  {
    auto rootContainer = std::make_unique<Wt::WContainerWidget>();
    auto outerContainer = rootContainer->setLayout(std::make_unique<Wt::WBorderLayout>());

    auto container = std::make_unique<Wt::WContainerWidget>();
    container->addNew<Wt::WText>("WLAN SSID:");
    auto ssidEdit = container->addNew<Wt::WLineEdit>();
    ssidEdit->setPlaceholderText("SSID");

    container->addNew<Wt::WBreak>();

    container->addNew<Wt::WText>("WLAN password:");
    auto passwdEdit = container->addNew<Wt::WLineEdit>();
    passwdEdit->setPlaceholderText("Password");

    auto page = std::make_unique<Wt::WPanel>();
    page->setCentralWidget(std::move(container));
    page->setMaximumSize(maxWidth_, 500);

    outerContainer->addWidget(std::move(page), Wt::LayoutPosition::Center);

    ok_ = outerContainer->addWidget(std::make_unique<Wt::WPushButton>("Ok"), Wt::LayoutPosition::South);
    ok_->disable();
    ok_->setMaximumSize(maxWidth_, 100);

    return std::move(rootContainer);
  }

} // namespace wuci
