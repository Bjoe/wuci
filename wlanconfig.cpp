#include "wlanconfig.hpp"

#include <Wt/WPanel.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WContainerWidget.h>

namespace wuci {

  WlanConfig::WlanConfig()
  {
  }

  std::unique_ptr<Wt::WWidget> WlanConfig::preparePage()
  {
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
    return std::move(page);
  }

} // namespace wuci
