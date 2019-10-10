#ifndef WUCI_ERROR_H
#define WUCI_ERROR_H

#include <string>

namespace wuci {

class ErrorCode
{
public:
    enum State {
        OK,
        ERROR
    };

    ErrorCode() = default;
    ErrorCode(std::string error);

    State state() const;
    std::string error() const;
private:
    State state_ = {OK};
    std::string error_ = {"Ok"};
};

} // namespace wuci

#endif // WUCI_ERROR_H
