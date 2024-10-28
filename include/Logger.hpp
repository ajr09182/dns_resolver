#pragma once
#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class Logger {
public:
    explicit Logger(const std::string& filename);
    ~Logger();

    void log(LogLevel level, const std::string& message);
    void setLogLevel(LogLevel level);

private:
    std::ofstream logFile;
    std::mutex logMutex;
    LogLevel currentLevel;

    static std::string levelToString(LogLevel level);
    static std::string getTimestamp();
};
