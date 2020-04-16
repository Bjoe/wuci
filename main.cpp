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

#include "webmain.hpp"

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
  auto app = std::make_unique<Wt::WApplication>(env);

  return app;
}

int main(int argc, char **argv)
{
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

    server.addEntryPoint(Wt::EntryPointType::Application,
                         [] (const Wt::WEnvironment& env) -> std::unique_ptr<Wt::WApplication>
    {
        auto main = std::make_unique<wuci::WebMain>(env);
        main->prepareWlanConfigPage();
        main->prepareVpnConfigPage();
        return std::move(main);
    });

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
