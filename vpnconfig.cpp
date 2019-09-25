#include "vpnconfig.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WBorderLayout.h>

namespace wuci {

  VpnConfig::VpnConfig()
  {
  }

  std::unique_ptr<Wt::WWidget> VpnConfig::preparePage()
  {
    auto rootContainer = std::make_unique<Wt::WContainerWidget>();
    auto container = rootContainer->setLayout(std::make_unique<Wt::WBorderLayout>());
    container->setSpacing(20);
    auto selectionBox = container->addWidget(std::make_unique<Wt::WSelectionBox>(), Wt::LayoutPosition::Center);

    selectionBox->addItem("Home");
    selectionBox->addItem("Office");
    selectionBox->addItem("Outside");

    ok_ = container->addWidget(std::make_unique<Wt::WPushButton>("Ok"), Wt::LayoutPosition::South);
    ok_->disable();

    selectionBox->changed().connect(
      [this, selectionBox]{
        if(selectionBox->currentIndex() != -1)
          {
            ok_->enable();
          }
      });

    return std::move(rootContainer);
  }

  void VpnConfig::connect(std::function<void()> callback)
  {
    ok_->clicked().connect(callback);
  }

} // namespace wuci
