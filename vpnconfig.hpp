#ifndef WUCI_VPNCONFIG_HPP
#define WUCI_VPNCONFIG_HPP

#include <Wt/WWidget.h>
#include <memory>
#include <functional>

namespace Wt {
    class WPushButton;
}

namespace wuci {

  class VpnConfig
  {
  public:
    VpnConfig();

    std::unique_ptr<Wt::WWidget> preparePage();

    void connect(std::function<void()> callback);

  private:
    Wt::WPushButton* ok_ = {};
  };

} // namespace wuci

#endif // WUCI_VPNCONFIG_HPP
