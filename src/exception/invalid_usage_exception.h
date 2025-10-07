#pragma once
#include <stdexcept>
#include <string>

namespace cl
{
class InvalidUsageException : public std::runtime_error
{
public:
  InvalidUsageException(const std::string &message) : std::runtime_error(message)
  {
  }
};
} // namespace cl