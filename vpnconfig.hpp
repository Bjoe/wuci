#ifndef WUCI_VPNCONFIG_HPP
#define WUCI_VPNCONFIG_HPP

#include <Wt/WWidget.h>
#include <Wt/WLength.h>
#include <memory>
#include <functional>
#include <tuple>
#include <optional>

namespace Wt {
    class WPushButton;
}

namespace wuci {

  class VpnConfig
  {
  public:
    static std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<VpnConfig>> createPage(Wt::WLength maxWidth);

    void connect(std::function<void()> callback);

  private:
    VpnConfig(Wt::WPushButton* okButton);

    Wt::WPushButton* okButton_;
  };

} // namespace wuci

#endif // WUCI_VPNCONFIG_HPP
