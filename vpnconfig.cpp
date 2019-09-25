#include "vpnconfig.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WPushButton.h>

namespace wuci {

  VpnConfig::VpnConfig()
  {
  }

  std::unique_ptr<Wt::WWidget> VpnConfig::preparePage()
  {
    auto container = std::make_unique<Wt::WContainerWidget>();
    auto selectionBox = container->addNew<Wt::WSelectionBox>();

    selectionBox->addItem("Home");
    selectionBox->addItem("Office");
    selectionBox->addItem("Outside");

    ok_ = container->addNew<Wt::WPushButton>("Ok");

    return std::move(container);
  }

  void VpnConfig::connect(std::function<void()> callback)
  {
    ok_->clicked().connect(callback);
  }

} // namespace wuci
