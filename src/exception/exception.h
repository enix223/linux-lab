#pragma once
#include <stdexcept>
#include <string>

namespace cl
{
class InvalidUsageException : public std::runtime_error
{
public:
  InvalidUsageException() : std::runtime_error("invalid usage")
  {
  }
};
} // namespace cl