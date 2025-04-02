#pragma once
#include <iostream>
#include <string>

// Simple logger for debug messages
namespace engine::core::log {
    enum class LogLevel {
        Info,
        Warning,
        Error
    };

    class Logger {
    public:
        static void log(const std::string& message, LogLevel level = LogLevel::Info) {
            switch (level) {
                case LogLevel::Info:    std::cout << "[INFO]    "; break;
                case LogLevel::Warning: std::cout << "[WARNING] "; break;
                case LogLevel::Error:   std::cout << "[ERROR]   "; break;
            }
            std::cout << message << std::endl;
        }
    };
}
