#include "logger.h"
#include "logFileManager.h"

namespace utils
{
std::queue<std::string> Logger::log_queue_;
std::mutex Logger::queue_mutex_;
std::condition_variable Logger::queue_condition_;
std::unique_ptr<std::thread> Logger::logging_thread_;
bool Logger::running_ = false;

void Logger::Init(const std::string &logDir)
{
  LogFileManager::Init(logDir); // ファイル管理を初期化

  running_ = true;
  logging_thread_ = std::make_unique<std::thread>(LoggingLoop);
}

void Logger::Log(LogLevel level, SubSystem subsystem, const std::string &message)
{
  std::lock_guard<std::mutex> lock(queue_mutex_);
  log_queue_.push({subsystem, "[" + ToString(level) + "] " + message});
  queue_condition_.notify_one();
}

void Logger::LoggingLoop()
{
  while (running_)
  {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    queue_condition_.wait(lock, []
                          { return !log_queue_.empty() || !running_; });

    while (!log_queue_.empty())
    {
      auto [subsys, message] = log_queue_.front();
      log_queue_.pop();
      lock.unlock();

      // ログ書き込み先の決定を依頼
      LogFileManager::WriteLog(subsys, message);

      lock.lock();
    }
  }
}

void Logger::Shutdown()
{
  running_ = false;
  queue_condition_.notify_all();

  if (logging_thread_ && logging_thread_->joinable())
  {
    logging_thread_->join();
  }

  LogFileManager::Shutdown();
}

std::string Logger::ToString(LogLevel level)
{
  switch (level)
  {
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARNING:
    return "WARNING";
  case LogLevel::ERROR:
    return "ERROR";
  case LogLevel::FATAL:
    return "FATAL";
  default:
    return "UNKNOWN";
  }
}

std::string Logger::ToString(SubSystem subsystem)
{
  return LogFileManager::GetFileName(subsystem);
}
}; // namespace utils
