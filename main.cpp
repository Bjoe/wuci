#include <Wt/WApplication.h>
#include <Wt/WServer.h>

#include <memory>

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
  auto app = std::make_unique<Wt::WApplication>(env);
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
