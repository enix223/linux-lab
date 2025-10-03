#pragma once
#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <thread>

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<Clock>;
using Duration = std::chrono::nanoseconds;

namespace cl
{
class RealTimeClock
{
public:
  using TimeTickCallback = std::function<void(std::tm *time)>;

  RealTimeClock() = default;

  ~RealTimeClock()
  {
    stop();
  }

  void start();
  void stop();
  void setTimerTickCallback(TimeTickCallback callback)
  {
    callback_ = callback;
  }

  std::tm *now()
  {
    return currentTime_;
  }

  std::string nowString();

  std::string formatTime(std::tm *time);

private:
  std::atomic<bool> running_{false};
  std::tm *currentTime_{nullptr};
  TimeTickCallback callback_{nullptr};
  std::thread timerThread_;

  void loop();
};
}; // namespace cl
