#include "logger.h"
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

class ThreadWithMutex
{
public:
  ThreadWithMutex() : thread_(&ThreadWithMutex::worker_thread, this)
  {
    thread_.detach();
  };

  ~ThreadWithMutex() = default;

  void wait()
  {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [this] { return this->finished_; });
  }

private:
  std::mutex mtx_;
  bool finished_ = false;
  std::condition_variable cv_;
  std::thread thread_;

  void worker_thread()
  {
    int i = 0;
    auto &logger = cl::Logger::getInstance();
    logger.info("ThreadWithMutex: started");
    for (i = 0; i < 3; i++)
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      logger.info("ThreadWithMutex: sleep", i);
    }
    logger.info("ThreadWithMutex: ended");
    {
      std::lock_guard<std::mutex> lock(mtx_);
      finished_ = true;
    }
    cv_.notify_one();
  }
};

class ThreadWithPromise
{
public:
  ThreadWithPromise()
  {
    // promsie is used to set value
    std::promise<bool> resultPromise_;
    // future is used to get value from promise
    resultFuture_ = resultPromise_.get_future();
    thread_ = std::thread{&ThreadWithPromise::worker_thread, this, std::move(resultPromise_)};
    thread_.detach();
  }

  void wait()
  {
    resultFuture_.get();
  }

private:
  std::future<bool> resultFuture_;
  std::thread thread_;

  void worker_thread(std::promise<bool> promise)
  {
    int i = 0;
    auto &logger = cl::Logger::getInstance();
    logger.info("ThreadWithPromise: started");
    for (i = 0; i < 4; i++)
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      logger.info("ThreadWithPromise: sleep", i);
    }
    logger.info("ThreadWithPromise: ended");
    promise.set_value(true);
  }
};

int main(int argv, const char *argc[])
{
  auto &logger = cl::Logger::getInstance();
  logger.info("main started");
  ThreadWithMutex t1;
  t1.wait();

  ThreadWithPromise t2;
  t2.wait();
  logger.info("main ended");
  return 0;
}
