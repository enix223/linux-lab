#pragma once

namespace cl
{
class BaseCommand
{
public:
  BaseCommand(int argv, const char *argc[]) : argv_(argv)
  {
    for (int i = 0; i < argv; i++)
    {
      argc_.push_back(argc[i]);
    }
  }

  std::string &getCommandName()
  {
    return argc_[0];
  }

  virtual ~BaseCommand()
  {
  }

  virtual void run() = 0;

protected:
  int argv_;
  std::vector<std::string> argc_;
};
} // namespace cl
