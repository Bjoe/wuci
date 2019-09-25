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
    ok_ = container->addNew<Wt::WPushButton>("Ok");
    ok_->disable();

    auto selectionBox = container->addNew<Wt::WSelectionBox>();

    selectionBox->addItem("Home");
    selectionBox->addItem("Office");
    selectionBox->addItem("Outside");

    selectionBox->changed().connect(
      [this, selectionBox]{
        if(selectionBox->currentIndex() != -1)
          {
            ok_->enable();
          }
      });

    return std::move(container);
  }

  void VpnConfig::connect(std::function<void()> callback)
  {
    ok_->clicked().connect(callback);
  }

} // namespace wuci
