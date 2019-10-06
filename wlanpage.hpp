#ifndef WUCI_WLANCONFIG_HPP
#define WUCI_WLANCONFIG_HPP

#include <Wt/WWidget.h>
#include <Wt/WLength.h>
#include <memory>
#include <tuple>
#include <optional>

#include "wlanconfig.hpp"

namespace Wt {
    class WPushButton;
}

namespace wuci {

  class WlanPage
  {
  public:

    static std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<WlanPage>> create(Wt::WLength maxWidth);

  private:
    WlanPage(WlanConfig wlanConfig, Wt::WPushButton* okButton);

    WlanConfig wlanConfig_;
    Wt::WPushButton* okButton_ = {};
  };

} // namespace wuci

#endif // WUCI_WLANCONFIG_HPP
