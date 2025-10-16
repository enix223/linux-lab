#include "base_command.h"
#include "exception.h"
#include "logger.h"
#include <cerrno>
#include <cstring>
#include <fstream>
#include <string>

class CopyWithStdLib : public cl::BaseCommand
{
public:
  CopyWithStdLib(int argc, const char *argv[]) : cl::BaseCommand(argc, argv) {};

  void usage() override
  {
    std::cerr << std::format("usage: {} <source file> <dest file>\n", getCommandName());
  }

  int run() override
  {
    auto &logger = cl::Logger::getInstance();
    if (argc_ != 3)
    {
      throw cl::InvalidUsageException();
    }

    auto &source = argv_[1];
    auto &target = argv_[2];

    std::ifstream ifile(source, std::ios::binary);
    if (!ifile)
    {
      logger.error(std::format("failed to open source file {}: {}", source, std::strerror(errno)));
      return -1;
    }

    std::ofstream ofile(target, std::ios::trunc | std::ios::out);
    if (!ofile)
    {
      logger.error(std::format("failed to open target file {}: {}", target, std::strerror(errno)));
      return -2;
    }

    std::vector<char> buffer(1024);
    while (ifile)
    {
      ifile.read(buffer.data(), buffer.size());
      auto read = ifile.gcount();
      if (read > 0)
      {
        ofile.write(buffer.data(), read);
        if (!ofile)
        {
          logger.error(std::format("failed to write to target file {}: {}", target, std::strerror(errno)));
          return -3;
        }
      }
    }
    if (!ifile.eof())
    {
      logger.error(std::format("failed to read file {}: {}", target, std::strerror(errno)));
      return -4;
    }

    return 0;
  }
};

int main(int argc, const char *argv[])
{
  auto &logger = cl::Logger::getInstance();
  CopyWithStdLib cmd{argc, argv};

  try
  {
    cmd.run();
  }
  catch (const cl::InvalidUsageException &e)
  {
    cmd.usage();
  }

  return 0;
}