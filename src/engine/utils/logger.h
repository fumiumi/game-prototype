#pragma once

#include <string>
#include <mutex>
#include <fstream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <map>

namespace utils
{
enum class LogLevel
{
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  FATAL,
  NUM_LOG_LEVELS
};

enum class SubSystem
{
  CORE,
  RENDER,
  INPUT,
  PHYSICS,
  COLLISION,
  AUDIO,
  SCENE,
  AI,
  UI,
  NETWORK,
  NUM_SUBSYSTEMS
};

inline SubSystem begin(SubSystem) { return SubSystem::CORE; }
inline SubSystem end(SubSystem) { return SubSystem::NUM_SUBSYSTEMS; }

inline SubSystem& operator++(SubSystem& e)
{
    e = static_cast<SubSystem>(static_cast<int>(e) + 1);
    return e;
}


/// @brief システム内で唯一のロガークラス
class Logger
{
public:
    static void Init(const std::string& logDir);
    static void Log(LogLevel level, SubSystem subsystem, const std::string& message);
    static void Shutdown();

private:
    static std::queue<std::pair<SubSystem, std::string>> log_queue_;
    static std::mutex queue_mutex_;
    static std::condition_variable queue_condition_;
    static std::unique_ptr<std::thread> logging_thread_;
    static bool running_;

    static void LoggingLoop();

    static std::string ToString(LogLevel level);
    static std::string ToString(SubSystem subsystem);
};
}; // namespace utils