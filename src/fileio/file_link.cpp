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
    const auto filename1 = "temp1.txt";
    const auto filename2 = "temp2.txt";
    auto &logger = cl::Logger::getInstance();
    int fd1 = open(filename1, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0)
    {
      logger.error(std::format("failed to open file: {}", std::strerror(errno)));
      return -1;
    }
    int fd2 = open(filename2, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd1 < 0)
    {
      logger.error(std::format("failed to open file: {}", std::strerror(errno)));
      return -1;
    }

    if (unlink(filename1) < 0)
    {
      logger.error(std::format("failed to unlink file: {}", std::strerror(errno)));
      return -2;
    }

    std::string msg = "hello world";
    if (write(fd1, msg.c_str(), msg.size()) < 0)
    {
      logger.error(std::format("failed to unlink file: {}", std::strerror(errno)));
      return -3;
    }

    std::cout << "press any key to continue";
    getchar();

    if (unlink(filename2) < 0)
    {
      logger.error(std::format("failed to unlink file: {}", std::strerror(errno)));
      return -2;
    }

    close(fd1);
    close(fd2);

    return 0;
  }
};

int main(int argc, const char *argv[])
{
  FileLink fileLink(argc, argv);
  fileLink.run();
}