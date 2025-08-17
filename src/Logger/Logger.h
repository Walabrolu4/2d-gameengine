#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

// LOGGER CLASS SUCKS IT SHOULD BE REPLACED WITH A LIBRARY

enum LogType { LOG_INFO, LOG_WARNING, LOG_ERROR };

struct LogEntry {
  int id;
  LogType type;
  std::string message;
};

class Logger {
 public:
  static std::vector<LogEntry> messages;
  static void Log(const std::string& message);
  static void Err(const std::string& message);
  static void Warn(const std::string& message);

 private:
  static std::string GetCurrentTimeString();
  static int curId;
};
#endif
