#pragma once

#include <string>
#include <vector>

namespace cl
{
class BaseCommand
{
public:
  BaseCommand(int argc, const char *argv[]) : argv_(argc)
  {
    for (int i = 0; i < argc; i++)
    {
      argv_.push_back(argv[i]);
    }
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
