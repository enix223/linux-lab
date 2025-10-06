#include "logger.h"
#include <thread>

void worker_thread()
{
  int i = 0;
  auto &logger = cl::Logger::getInstance();
  logger.info("worker started");
  for (i = 0; i < 10; i++)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    logger.info("sleep", i);
  }
  logger.info("worker ended");
}

int main(int argv, const char *argc[])
{
  std::thread t1{worker_thread};
  t1.join();
  return 0;
}