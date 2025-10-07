#include "base_command.h"
#include "invalid_usage_exception.h"
#include <iostream>
#include <sstream>
#include <string>
#include <sys/io.h>
#include <unistd.h>
#include <vector>

class CopyWithSysInvoke : public cl::BaseCommand
{
public:
  CopyWithSysInvoke(int argv, const char *argc[]) : cl::BaseCommand(argv, argc)
  {
    if (argv != 3)
    {
      throw cl::InvalidUsageException(usage());
    }
  }

  void run() override
  {
    auto source = argc_[1];
    auto target = argc_[2];
  }

  std::string usage()
  {
    std::stringstream oss;
    oss << "usage: " << getCommandName() << "<source file> <dest file>" << std::endl;
    return oss.str();
  }
};

int main(int argv, const char *argc[])
{
  CopyWithSysInvoke cmd{argv, argc};
  cmd.run();
}
