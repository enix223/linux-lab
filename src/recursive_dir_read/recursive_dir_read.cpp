#include "base_command.h"
#include "exception.h"
#include "logger.h"
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

class RecursiveDirRead : public cl::BaseCommand
{
public:
  RecursiveDirRead(int argc, const char *argv[]) : cl::BaseCommand(argc, argv) {};

  int run() override
  {
    if (argc_ != 2)
    {
      throw cl::InvalidUsageException();
    }

    auto &path = argv_[1];
    loop(path);

    return 0;
  }

  void usage() override
  {
    std::cerr << std::format("usage: {} <dir>", getCommandName()) << std::endl;
  }

private:
  void loop(const std::string &path)
  {
    auto &logger = cl::Logger::getInstance();
    DIR *dir = opendir(path.c_str());
    if (dir == nullptr)
    {
      logger.error(std::format("failed to open dir {}: {}", path, std::strerror(errno)));
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      {
        // skip current dir & parent dir
        continue;
      }
      auto fullPath = path + "/" + entry->d_name;
      logger.info(fullPath.c_str());

      struct stat statBuf;
      if (stat(fullPath.c_str(), &statBuf) == 0)
      {
        if (S_ISDIR(statBuf.st_mode))
        {
          loop(fullPath);
        }
      }
    }

    closedir(dir);
  }
};

int main(int argc, const char *argv[])
{
  auto &logger = cl::Logger::getInstance();
  RecursiveDirRead cmd(argc, argv);
  try
  {
    cmd.run();
  }
  catch (const cl::InvalidUsageException &e)
  {
    cmd.usage();
  }
}
