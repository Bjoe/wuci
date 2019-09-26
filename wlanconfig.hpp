#ifndef WUCI_WLANCONFIG_HPP
#define WUCI_WLANCONFIG_HPP

#include <Wt/WWidget.h>
#include <Wt/WLength.h>
#include <memory>

namespace Wt {
    class WPushButton;
}

namespace wuci {

  class WlanConfig
  {
  public:
    WlanConfig();

    std::unique_ptr<Wt::WWidget> preparePage();

  private:
    Wt::WLength maxWidth_ = {500};
    Wt::WPushButton* ok_ = {};
  };

} // namespace wuci

#endif // WUCI_WLANCONFIG_HPP
