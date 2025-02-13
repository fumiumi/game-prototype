#include "logFileManager.h"
#include "logger.h"
#include <iostream>
#include <filesystem>

namespace utils
{
std::mutex LogFileManager::file_mutex_;
std::map<SubSystem, std::ofstream> LogFileManager::log_files_;

void LogFileManager::Init(const std::string &logDir)
{
  std::lock_guard<std::mutex> lock(file_mutex_);
  std::filesystem::create_directories(logDir); // ディレクトリがなければ作成

  for (auto subsystem : SubSystem)
  {
    std::string filename = logDir + "/" + GetFileName(subsystem);
    log_files_[subsystem].open(filename, std::ios::out | std::ios::app);
    if (!log_files_[subsystem])
    {
      std::cerr << "[LOG ERROR] Failed to open log file: " << filename << std::endl;
    }
  }
}

void LogFileManager::WriteLog(SubSystem subsystem, const std::string &message)
{
  std::lock_guard<std::mutex> lock(file_mutex_);
  if (log_files_.count(subsystem))
  {
    log_files_[subsystem] << message << std::endl;
  }
}

void LogFileManager::Shutdown()
{
  std::lock_guard<std::mutex> lock(file_mutex_);
  for (auto &pair : log_files_)
  {
    if (pair.second.is_open())
    {
      pair.second.close();
    }
  }
}

std::string LogFileManager::GetFileName(SubSystem subsystem)
{
  switch (subsystem)
  {
  case SubSystem::CORE:
    return "core.log";
  case SubSystem::RENDER:
    return "render.log";
  case SubSystem::INPUT:
    return "input.log";
  case SubSystem::PHYSICS:
    return "physics.log";
  case SubSystem::COLLISION:
    return "collision.log";
  case SubSystem::AUDIO:
    return "audio.log";
  case SubSystem::SCENE:
    return "scene.log";
  case SubSystem::AI:
    return "ai.log";
  case SubSystem::UI:
    return "ui.log";
  case SubSystem::NETWORK:
    return "network.log";
  default:
    return "unknown.log";
  }
}
}; // namespace utils
