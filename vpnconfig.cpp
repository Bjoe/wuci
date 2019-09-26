#include "vpnconfig.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WBorderLayout.h>

namespace wuci {

  VpnConfig::VpnConfig(Wt::WPushButton *okButton) : okButton_(okButton)
  {
  }

  std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<VpnConfig> > VpnConfig::createPage(Wt::WLength maxWidth)
  {
    auto rootContainer = std::make_unique<Wt::WContainerWidget>();
    rootContainer->setId("rootContainer-vpnconfig");
    auto container = rootContainer->setLayout(std::make_unique<Wt::WBorderLayout>());
    container->setSpacing(20);
    auto selectionBox = container->addWidget(std::make_unique<Wt::WSelectionBox>(), Wt::LayoutPosition::Center);

    selectionBox->setMaximumSize(maxWidth, 300);

    selectionBox->addItem("Home");
    selectionBox->addItem("Office");
    selectionBox->addItem("Outside");

    auto okButton = container->addWidget(std::make_unique<Wt::WPushButton>("Ok"), Wt::LayoutPosition::South);
    okButton->disable();
    okButton->setMaximumSize(maxWidth, 100);

    selectionBox->changed().connect(
      [okButton, selectionBox]{
        if(selectionBox->currentIndex() != -1)
          {
            okButton->enable();
          }
      });

    return std::make_tuple(std::move(rootContainer), VpnConfig(okButton));
  }

  void VpnConfig::connect(std::function<void()> callback)
  {
    okButton_->clicked().connect(callback);
  }

} // namespace wuci
