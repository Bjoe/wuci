#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WBreak.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPanel.h>
#include <Wt/WStackedWidget.h>
#include <memory>

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
  auto app = std::make_unique<Wt::WApplication>(env);

  app->setTitle("Open-W-UCI");

  auto rootContainer = app->root();

  auto stackedWidget = rootContainer->addNew<Wt::WStackedWidget>();


  auto vpnContainer = std::make_unique<Wt::WContainerWidget>();

  auto *sb1 = vpnContainer->addNew<Wt::WSelectionBox>();
  sb1->addItem("Home");
  sb1->addItem("Office");
  sb1->addItem("Outside");
  sb1->setCurrentIndex(1); // Select 'medium' by default.
  sb1->setMargin(10, Wt::Side::Right);

  Wt::WText *out = vpnContainer->addNew<Wt::WText>("");

  sb1->activated().connect([=] {
      stackedWidget->setCurrentIndex(1);
      //out->setText(Wt::WString("You selected {1}.")
      //             .arg(sb1->currentText()));
  });

  stackedWidget->addWidget(std::move(vpnContainer));




  auto panel = std::make_unique<Wt::WPanel>();

  auto container = std::make_unique<Wt::WContainerWidget>();
  container->addNew<Wt::WText>("WLAN SSID:");
  Wt::WLineEdit *ssidEdit = container->addNew<Wt::WLineEdit>();
  ssidEdit->setPlaceholderText("SSID");

  Wt::WText *out1 = rootContainer->addNew<Wt::WText>("");
  ssidEdit->keyPressed().connect([=] (const Wt::WKeyEvent& e) {
      out1->setText("You pressed the '" + e.text() + "' key.");
  });

  container->addNew<Wt::WBreak>();

  container->addNew<Wt::WText>("WLAN passwd:");
  Wt::WLineEdit *passwdEdit = container->addNew<Wt::WLineEdit>();
  passwdEdit->setPlaceholderText("Password");

  Wt::WText *out2 = rootContainer->addNew<Wt::WText>("");

  panel->setCentralWidget(std::move(container));


  stackedWidget->addWidget(std::move(panel));

  return app;
}

int main(int argc, char **argv)
{
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

    server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
