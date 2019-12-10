#ifndef WUCI_VPNCONFIG_HPP
#define WUCI_VPNCONFIG_HPP

#include <memory>
#include <functional>
#include <tuple>
#include <optional>

#include <Wt/WWidget.h>
#include <Wt/WLength.h>

namespace Wt {
    class WPushButton;
}

namespace wuci {

  class VpnPage
  {
  public:
    static std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<VpnPage>> create(Wt::WLength maxWidth);

    void connect(std::function<void()> callback);

  private:
    VpnPage(Wt::WPushButton* okButton);

    Wt::WPushButton* okButton_ = {};
  };

} // namespace wuci

#endif // WUCI_VPNCONFIG_HPP
