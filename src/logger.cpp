#include "Logger.h"

#include <chrono>
#include <ctime>
#include <iostream>

std::vector<LogEntry> Logger::messages;
int Logger::curId = 0;

void Logger::Log(const std::string& message) {
  std::string time = GetCurrentTimeString();

  LogEntry entry;
  entry.type = LOG_INFO;
  entry.id = curId;
  curId++;
  entry.message = "LOG[" + time + "]  : " + message;

  std::cout << "\x1b[32m" << entry.message << "\x1b[0m \n";
  Logger::messages.push_back(entry);
}

void Logger::Err(const std::string& message) {
  std::string time = GetCurrentTimeString();

  LogEntry entry;
  entry.type = LOG_ERROR;
  entry.id = curId;
  curId++;
  entry.message = "ERR[" + time + "]  : " + message;

  std::cout << "\x1b[31m" << "ERR [" << time << "]" << ":" << message
            << "\x1b[0m \n";
}

void Logger::Warn(const std::string& message) {
  std::string time = GetCurrentTimeString();

  LogEntry entry;
  entry.type = LOG_WARNING;
  entry.id = curId;
  curId++;
  entry.message = "LOG[" + time + "]  : " + message;

  std::cout << "\x1b[31m" << "ERR [" << time << "]" << ":" << message
            << "\x1b[0m \n";
  Logger::messages.push_back(entry);
}

std::string Logger::GetCurrentTimeString() {
  auto now = std::chrono::system_clock::now();
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&currentTime);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%m-%d-%Y %H:%M:%S", localTime);
  return std::string(buffer);
}
