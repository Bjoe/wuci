#include "wlanpage.hpp"

#include <Wt/WPanel.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WPushButton.h>

#include <variant>

#include "wlanconfig.hpp"
#include "errorcode.hpp"

// helper type for teh visitor. Will be introduced in C++20
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

namespace wuci {

  WlanPage::WlanPage(Wt::WPushButton *okButton) : okButton_(okButton)
  {
  }

  std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<WlanPage> > WlanPage::create(Wt::WLength maxWidth)
  {
    auto rootContainer = std::make_unique<Wt::WContainerWidget>();

    auto wlc = WlanConfig::create();
    if(wlc)
    {
        auto wlanUciConfig = wlc.value();
        auto outerContainer = rootContainer->setLayout(std::make_unique<Wt::WBorderLayout>());

        auto container = std::make_unique<Wt::WContainerWidget>();
        container->addNew<Wt::WText>("WLAN SSID:");
        auto ssidEdit = container->addNew<Wt::WLineEdit>();
        ssidEdit->setPlaceholderText("SSID");

        std::visit(overloaded {
                       [ssidEdit](std::string v){ ssidEdit->setText(v); },
                       [](wuci::ErrorCode){} // TODO improve error
                   }, wlanUciConfig.ssid());

        container->addNew<Wt::WBreak>();

        container->addNew<Wt::WText>("WLAN password:");
        auto passwdEdit = container->addNew<Wt::WLineEdit>();
        passwdEdit->setPlaceholderText("Password");

        std::visit(overloaded {
                       [passwdEdit](std::string v){ passwdEdit->setText(v); },
                       [](wuci::ErrorCode){} // TODO improve error
                   }, wlanUciConfig.key());

        auto page = std::make_unique<Wt::WPanel>();
        page->setCentralWidget(std::move(container));
        page->setMaximumSize(maxWidth, 500);

        outerContainer->addWidget(std::move(page), Wt::LayoutPosition::Center);

        auto okButton = outerContainer->addWidget(std::make_unique<Wt::WPushButton>("Ok"), Wt::LayoutPosition::South);
        //okButton->disable();
        okButton->setMaximumSize(maxWidth, 100);

        okButton->clicked().connect(
        [passwdEdit, ssidEdit](){
            Wt::WString psswd = passwdEdit->text();
            Wt::WString ssid = ssidEdit->text();
            auto u = WlanConfig::create();
            if(u)
            {
                auto w = u.value();
                auto retKey = w.setKey(psswd.toUTF8());
                Wt::log("info") << "setKey: " << retKey.error();
                auto retSSid = w.setSsid(ssid.toUTF8());
                Wt::log("info") << "setSsid: " << retSSid.error();

            }
        });

        return std::make_tuple(std::move(rootContainer), WlanPage(okButton));
    }
    else
    {
        // TODO Improve error
        return std::make_tuple(std::move(rootContainer), std::nullopt);
    }
  }

  void WlanPage::connect(std::function<void ()> callback)
  {

  }

} // namespace wuci
