#ifndef WUCI_ERROR_H
#define WUCI_ERROR_H

#include <string>

namespace wuci {

class Error
{
public:
    Error(std::string error);

    std::string error() const;
private:
    std::string error_ = {};
};

} // namespace wuci

#endif // WUCI_ERROR_H
