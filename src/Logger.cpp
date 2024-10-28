#include "Logger.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>

Logger::Logger(const std::string& filename)
    : logFile(filename, std::ios::app)
    , currentLevel(LogLevel::INFO) {
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < currentLevel) return;

    std::lock_guard<std::mutex> lock(logMutex);
    logFile << getTimestamp() << " [" << levelToString(level) << "] "
            << message << std::endl;
}

void Logger::setLogLevel(LogLevel level) {
    currentLevel = level;
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::FATAL:   return "FATAL";
        default:               return "UNKNOWN";
    }
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}