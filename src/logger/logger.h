#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace cl
{
/**
 * @brief Simple, thread-safe logger implementation with configurable levels.
 * * Uses the Singleton pattern for easy global access and a mutex for thread safety
 * during output operations.
 */
class Logger
{
public:
  // Define logging levels
  enum class Level
  {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    OFF // Highest level, effectively disables all logging
  };

  /**
   * @brief Singleton accessor method.
   */
  static Logger &getInstance()
  {
    static Logger instance;
    return instance;
  }

  // Delete copy constructor and assignment operator for Singleton
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  /**
   * @brief Sets the minimum logging level threshold.
   * Messages with a lower priority than this level will be ignored.
   * @param newLevel The new minimum level to log.
   */
  void setLevel(Level newLevel)
  {
    currentLevel_ = newLevel;
    std::cerr << "Logger level set to: " << levelToString(newLevel) << std::endl;
  }

  // --- Logging Methods ---

  template <typename... Args> void debug(const Args &...messages)
  {
    log(Level::DEBUG, messages...);
  }

  template <typename... Args> void info(const Args &...messages)
  {
    log(Level::INFO, messages...);
  }

  template <typename... Args> void warn(const Args &...messages)
  {
    log(Level::WARN, messages...);
  }

  template <typename... Args> void error(const Args &...messages)
  {
    log(Level::ERROR, messages...);
  }

private:
  Level currentLevel_ = Level::INFO; // Default minimum level
  std::mutex outputMutex_;

  // Private constructor for Singleton pattern
  Logger() = default;

  /**
   * @brief Converts Level enum to its string representation.
   */
  static std::string levelToString(Level level)
  {
    static const std::map<Level, std::string> levelMap = {{Level::DEBUG, "DEBUG"},
                                                          {Level::INFO, "INFO "},
                                                          {Level::WARN, "WARN "},
                                                          {Level::ERROR, "ERROR"},
                                                          {Level::OFF, "OFF  "}};
    auto it = levelMap.find(level);
    return (it != levelMap.end()) ? it->second : "UNKNOWN";
  }

  /**
   * @brief Helper function to get the current timestamp string.
   */
  std::string getTimestamp() const
  {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    // Use localtime_r for thread-safety (preferred on POSIX systems)
    // If not available, std::localtime is used as a fallback but is not thread-safe.
    std::tm local_tm;
#ifdef __GNUC__
    // Use the thread-safe version where available
    if (localtime_r(&current_time, &local_tm) == nullptr)
    {
      std::cerr << "Error: localtime_r failed." << std::endl;
    }
#else
    // Fallback for systems without localtime_r
    std::tm *tm_ptr = std::localtime(&current_time);
    if (tm_ptr)
    {
      local_tm = *tm_ptr;
    }
    else
    {
      std::cerr << "Error: std::localtime failed." << std::endl;
    }
#endif

    std::stringstream ss;
    ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
  }

  /**
   * @brief Core logging function.
   */
  template <typename... Args> void log(Level level, const Args &...messages)
  {
    // Check if the message level meets or exceeds the current minimum threshold
    if (level < currentLevel_)
    {
      return;
    }

    // Lock the mutex before outputting to ensure thread-safe operation
    std::lock_guard<std::mutex> lock(outputMutex_);

    // Choose output stream: std::cerr for warnings/errors, std::cout otherwise
    std::ostream &os = (level >= Level::WARN) ? std::cerr : std::cout;

    os << "[" << getTimestamp() << "] "
       << "[" << levelToString(level) << "] ";

    // Print all messages recursively
    ((os << messages), ...);

    os << std::endl;
  }
};
} // namespace cl