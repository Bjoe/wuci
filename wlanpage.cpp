#include "wlanpage.hpp"

#include <Wt/WPanel.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WPushButton.h>

#include <variant>

#include "error.hpp"

// helper type for teh visitor. Will be introduced in C++20
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

namespace wuci {

  WlanPage::WlanPage(WlanConfig wlanConfig, Wt::WPushButton *okButton) : wlanConfig_(std::move(wlanConfig)), okButton_(okButton)
  {
  }

  std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<WlanPage> > WlanPage::create(Wt::WLength maxWidth)
  {
    auto rootContainer = std::make_unique<Wt::WContainerWidget>();

    auto wlc = WlanConfig::create();
    if(wlc)
    {
        auto w = wlc.value();
        auto outerContainer = rootContainer->setLayout(std::make_unique<Wt::WBorderLayout>());

        auto container = std::make_unique<Wt::WContainerWidget>();
        container->addNew<Wt::WText>("WLAN SSID:");
        auto ssidEdit = container->addNew<Wt::WLineEdit>();
        ssidEdit->setPlaceholderText("SSID");

        std::visit(overloaded {
                       [ssidEdit](std::string v){ ssidEdit->setText(v); },
                       [](wuci::Error){} // TODO improve error
                   }, w.ssid());

        container->addNew<Wt::WBreak>();

        container->addNew<Wt::WText>("WLAN password:");
        auto passwdEdit = container->addNew<Wt::WLineEdit>();
        passwdEdit->setPlaceholderText("Password");

        std::visit(overloaded {
                       [passwdEdit](std::string v){ passwdEdit->setText(v); },
                       [](wuci::Error){} // TODO improve error
                   }, w.key());

        auto page = std::make_unique<Wt::WPanel>();
        page->setCentralWidget(std::move(container));
        page->setMaximumSize(maxWidth, 500);

        outerContainer->addWidget(std::move(page), Wt::LayoutPosition::Center);

        auto okButton = outerContainer->addWidget(std::make_unique<Wt::WPushButton>("Ok"), Wt::LayoutPosition::South);
        okButton->disable();
        okButton->setMaximumSize(maxWidth, 100);

        return std::make_tuple(std::move(rootContainer), WlanPage(w, okButton));
    }
    else
    {
        // TODO Improve error
        return std::make_tuple(std::move(rootContainer), std::nullopt);
    }
  }

} // namespace wuci
