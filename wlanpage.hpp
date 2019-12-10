#ifndef WUCI_WLANCONFIG_HPP
#define WUCI_WLANCONFIG_HPP

#include <memory>
#include <functional>
#include <tuple>
#include <optional>

#include <Wt/WWidget.h>
#include <Wt/WLength.h>

#include "messagebus.hpp"

namespace Wt {
    class WPushButton;
}

namespace wuci {

  class WlanPage
  {
  public:

    static std::tuple<std::unique_ptr<Wt::WWidget>, std::optional<WlanPage>> create(std::optional<MessageBus> msgBus,
                                                                                    Wt::WLength maxWidth);

    void connect(std::function<void()> callback);

  private:
    WlanPage(Wt::WPushButton* okButtons);

    Wt::WPushButton* okButton_ = {};
  };

} // namespace wuci

#endif // WUCI_WLANCONFIG_HPP
