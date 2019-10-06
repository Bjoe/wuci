#include "error.hpp"

#include <algorithm>

namespace wuci {

Error::Error(std::string error) : error_(std::move(error))
{

}

std::string Error::error() const
{
    return error_;
}

} // namespace wuci
