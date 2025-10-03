#include "clock.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace cl
{
void RealTimeClock::start()
{
  if (timerThread_.joinable())
  {
    return;
  }
  running_ = true;
  timerThread_ = std::thread(&RealTimeClock::loop, this);
}

void RealTimeClock::stop()
{
  if (!timerThread_.joinable())
  {
    return;
  }

  running_ = false;
  timerThread_.join();
}

std::string RealTimeClock::nowString()
{
  return formatTime(currentTime_);
}

std::string RealTimeClock::formatTime(std::tm *time)
{
  std::stringstream ss;
  ss << std::put_time(time, "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

void RealTimeClock::loop()
{
  while (running_)
  {
    auto now = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::to_time_t(now);
    auto localTm = std::localtime(&currentTime);
    if (localTm)
    {
      currentTime_ = localTm;
      if (callback_ != nullptr)
      {
        callback_(currentTime_);
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
} // namespace cl
