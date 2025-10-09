#include "base_command.h"
#include "exception.h"
#include "logger.h"
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/io.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

class CopyWithSysInvoke : public cl::BaseCommand
{
public:
  CopyWithSysInvoke(int argc, const char *argv[]) : cl::BaseCommand(argc, argv)
  {
  }

  int run() override
  {
    auto &logger = cl::Logger::getInstance();
    if (argc_ != 3)
    {
      logger.info("argc = ", argc_);
      throw cl::InvalidUsageException();
    }

    auto &source = argv_[1];
    auto &target = argv_[2];

    auto in = open(source.c_str(), O_RDONLY);
    if (in < 0)
    {
      logger.error(std::format("failed to open file {}: {}", source, std::strerror(errno)));
      return -1;
    }

    struct stat fileStat;
    if (stat(source.c_str(), &fileStat) == -1)
    {
      logger.error(std::format("failed to stat file {}: {}", source, std::strerror(errno)));
      return -2;
    }
    auto permission = fileStat.st_mode & 0777;

    auto out = open(target.c_str(), O_WRONLY | O_CREAT | O_TRUNC, permission);
    if (in < 0)
    {
      logger.error(std::format("failed to stat file {}: {}", target, std::strerror(errno)));
      return -3;
    }

    uint8_t buf[1024];
    ssize_t n = 0, w = 0;
    while (true)
    {
      n = read(in, buf, sizeof(buf));
      if (n < 0)
      {
        logger.error(std::format("failed to read file {}: {}", target, std::strerror(errno)));
        return -4;
      }
      if (n == 0)
      {
        break;
      }

      w = write(out, buf, n);
      if (w < 0)
      {
        logger.error(std::format("failed to write file {}: {}", target, std::strerror(errno)));
        return -5;
      }
    }
    return 0;
  }

  void usage() override
  {
    std::stringstream oss;
    std::cerr << std::format("usage: {} <source file> <dest file>\n", getCommandName());
  }
};

int main(int argc, const char *argv[])
{
  auto &logger = cl::Logger::getInstance();
  CopyWithSysInvoke cmd{argc, argv};

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
