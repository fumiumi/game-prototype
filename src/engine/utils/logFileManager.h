#pragma once

#include <string>
#include <mutex>
#include <fstream>
#include <queue>
#include <map>

namespace utils
{
/// @brief サブシステムごとにログファイルを分別するためのクラス
class LogFileManager
{
public:
  static void Init(const std::string &logDir);
  static void WriteLog(SubSystem subsystem, const std::string &message);
  static void Shutdown();

private:
  static std::mutex file_mutex_;
  static std::map<SubSystem, std::ofstream> log_files_;

  static std::string GetFileName(SubSystem subsystem);
};
}; // namespace utils