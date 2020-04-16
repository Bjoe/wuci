#include "vpnuploadpage.hpp"

#include <Wt/WContainerWidget.h>
#include <Wt/WFileDropWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WText.h>
#include <Wt/Utils.h>
#include <Wt/WMessageBox.h>
#include <Wt/WTimer.h>

#include <chrono>
#include <iostream>
#include <fstream>

#include "universalconfig.hpp"

namespace wuci {

VpnUploadPage::VpnUploadPage(Wt::WPushButton *okButton, Wt::WText *state) : okButton_(okButton), state_(state)
{
}

std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<VpnUploadPage>> VpnUploadPage::create(std::optional<MessageBus> msgBus,
                                                                                             Wt::WLength maxWidth)
{
    auto rootContainer = std::make_unique<Wt::WContainerWidget>();
    rootContainer->setId("rootContainer-vpnupload");
    auto container = rootContainer->setLayout(std::make_unique<Wt::WBorderLayout>());
    container->setSpacing(20);
    container->addWidget(std::make_unique<Wt::WText>("<h3>Dropping openvpn configuration file in the widget below</h3>"), Wt::LayoutPosition::North);
    auto dropWidget = container->addWidget(std::make_unique<Wt::WFileDropWidget>(), Wt::LayoutPosition::Center);

    auto southContainer = std::make_unique<Wt::WContainerWidget>();

    auto state = southContainer->addNew<Wt::WText>("Ready");
    state->setInline(false);
    state->setTextFormat(Wt::TextFormat::XHTML);

    auto messageBox = rootContainer->addChild(std::make_unique<Wt::WMessageBox>("Reboot",
                                                                                "<p>System reboot .... wait 3 sec., then reload the page ...</p>",
                                                                                Wt::Icon::Information, Wt::StandardButton::None));
    auto restartTimer = rootContainer->addChild(std::make_unique<Wt::WTimer>());
    restartTimer->setInterval(std::chrono::seconds(2));
    restartTimer->setSingleShot(true);
    restartTimer->timeout().connect([messageBox, msgBus]{
        messageBox->show();
        msgBus->restartSystem();
    });

    Wt::WPushButton *okButton; // TODO Do we need push button?
    /*auto okButton = southContainer->addNew<Wt::WPushButton>("Ok");
    okButton->disable();
    okButton->setMaximumSize(maxWidth, 100);
*/
    dropWidget->drop().connect([=] (const std::vector<Wt::WFileDropWidget::File*>& files) {
      const int maxFiles = 1;
      auto prevNbFiles = dropWidget->uploads().size() - files.size();
      for (unsigned i=0; i < files.size(); i++) {
        if (prevNbFiles + i >= maxFiles) {
          dropWidget->cancelUpload(files[i]);
          continue;
        }

        Wt::WContainerWidget *block = dropWidget->addNew<Wt::WContainerWidget>();
        block->setToolTip(files[i]->clientFileName());
        block->addStyleClass("upload-block spinner");
      }

      if (dropWidget->uploads().size() >= maxFiles)
        dropWidget->setAcceptDrops(false);
    });

    dropWidget->uploaded().connect([=] (Wt::WFileDropWidget::File* file) {
      std::vector<Wt::WFileDropWidget::File*> uploads = dropWidget->uploads();
      std::size_t idx = 0;
      for (; idx != uploads.size(); ++idx)
      {
        if (uploads[idx] == file)
        {
            std::ofstream dest(OPENVPN_CONFIG_FILE_, std::ios::binary);
            if (dest.fail()) {
                Wt::log("Error") << "Failed to save openvpn configuration file";
                Wt::WMessageBox::show("VPN Fail",
                                          "Failed to save vpn configuration file",
                                          Wt::StandardButton::Ok);
              break;
            }
            std::string spool = file->uploadedFile().spoolFileName();
            std::ifstream src(spool.c_str(), std::ios::binary);
            dest << src.rdbuf();

            std::string fileName = Wt::Utils::htmlEncode(file->clientFileName());

            auto u = UniversalConfig::create();
            if(u && msgBus) {
                auto w = u.value();
                auto retEnc = w.enableOpenvpn();
                Wt::log("info") << "Enable OpenVPN: " << retEnc.error();
                //msgBus.value().restartProcess("openvpn"); TODO On First time there is no openvpn process
            }

            Wt::WMessageBox::show("VPN Ok",
                                      "<p>File <i>&quot;" + fileName + "&quot;</i> uploaded.</p>",
                                      Wt::StandardButton::Ok);
            restartTimer->start();
            break;
         }
      }
      dropWidget->widget(idx)->removeStyleClass("spinner");
      dropWidget->widget(idx)->addStyleClass("ready");
    });

    dropWidget->tooLarge().connect([=] (Wt::WFileDropWidget::File *file, uint64_t size) {
      std::vector<Wt::WFileDropWidget::File*> uploads = dropWidget->uploads();
      std::size_t idx = 0;
      for (; idx != uploads.size(); ++idx)
        if (uploads[idx] == file)
          break;
      dropWidget->widget(idx)->removeStyleClass("spinner");
      dropWidget->widget(idx)->addStyleClass("failed");
    });

    dropWidget->uploadFailed().connect([=] (Wt::WFileDropWidget::File *file) {
      std::vector<Wt::WFileDropWidget::File*> uploads = dropWidget->uploads();
      std::size_t idx = 0;
      for (; idx != uploads.size(); ++idx)
        if (uploads[idx] == file)
          break;
      dropWidget->widget(idx)->removeStyleClass("spinner");
      dropWidget->widget(idx)->addStyleClass("failed");
    });

    container->addWidget(std::move(southContainer), Wt::LayoutPosition::South);
    return std::make_tuple(std::move(rootContainer), VpnUploadPage(okButton, state));
}

void VpnUploadPage::connect(std::function<void ()> callback)
{
    okButton_->clicked().connect(callback);
}

} // namespace wuci
