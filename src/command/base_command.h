#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace cl
{
class BaseCommand
{
public:
  BaseCommand(int argc, const char *argv[]) : argc_(argc), argv_(std::vector<std::string>(argv, argv + argc))
  {
  }

  std::string &getCommandName()
  {
    return argv_[0];
  }

  virtual ~BaseCommand()
  {
  }

  virtual void usage() = 0;

  virtual int run() = 0;

protected:
  int argc_;
  std::vector<std::string> argv_;
};
} // namespace cl
