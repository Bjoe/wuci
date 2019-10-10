#include "errorcode.hpp"

#include <algorithm>

namespace wuci {

ErrorCode::ErrorCode(std::string error) : state_(ERROR), error_(std::move(error))
{}

ErrorCode::State ErrorCode::state() const
{
    return state_;
}

std::string ErrorCode::error() const
{
    return error_;
}

} // namespace wuci
