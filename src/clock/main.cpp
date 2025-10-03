#include "clock.h"
#include "logger.h"
#include <csignal>
#include <iostream>

cl::RealTimeClock realTimeClock;
std::atomic<bool> stop{false};

void signalHandler(int signum)
{
  if (signum == SIGINT)
  {
    // Set the global flag to terminate the main loop
    realTimeClock.stop();
    stop = true;
    cl::Logger &logger = cl::Logger::getInstance();
    logger.error("SIGINT received. Initiating graceful shutdown...");
  }
}

int main()
{
  cl::Logger &logger = cl::Logger::getInstance();
  if (std::signal(SIGINT, signalHandler) == SIG_ERR)
  {
    logger.error("Error: Cannot set SIGINT handler. Exiting.");
    return 1;
  }
  realTimeClock.setTimerTickCallback([](std::tm *now) {
    cl::Logger &logger = cl::Logger::getInstance();
    logger.info(realTimeClock.formatTime(now));
  });
  realTimeClock.start();

  while (!stop)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  realTimeClock.stop();
}