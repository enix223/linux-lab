#include "base_command.h"
#include "exception.h"
#include "logger.h"
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <string>

class FileLink : public cl::BaseCommand
{
public:
  FileLink(int argc, const char *argv[]) : cl::BaseCommand(argc, argv) {};

  void usage() override
  {
    std::cerr << std::format("usage: {}", getCommandName()) << std::endl;
  }

  int run() override
  {
    const auto filename = "temp.txt";
    auto &logger = cl::Logger::getInstance();
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
      logger.error(std::format("failed to open file: {}", std::strerror(errno)));
      return -1;
    }
    if (unlink(filename) < 0)
    {
      logger.error(std::format("failed to unlink file: {}", std::strerror(errno)));
      return -2;
    }
    return 0;
  }
};