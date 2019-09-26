#ifndef WUCI_WLANCONFIG_HPP
#define WUCI_WLANCONFIG_HPP

#include <Wt/WWidget.h>
#include <Wt/WLength.h>
#include <memory>
#include <tuple>
#include <optional>

namespace Wt {
    class WPushButton;
}

namespace wuci {

  class WlanConfig
  {
  public:

    static std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<WlanConfig>> createPage(Wt::WLength maxWidth);

  private:
    WlanConfig(Wt::WPushButton* okButton);

    Wt::WPushButton* okButton_;
  };

} // namespace wuci

#endif // WUCI_WLANCONFIG_HPP
