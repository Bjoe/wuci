#ifndef WUCI_WLANCONFIG_HPP
#define WUCI_WLANCONFIG_HPP

#include <Wt/WWidget.h>
#include <memory>

namespace wuci {

  class WlanConfig
  {
  public:
    WlanConfig();

    std::unique_ptr<Wt::WWidget> preparePage();

  private:
  };

} // namespace wuci

#endif // WUCI_WLANCONFIG_HPP
