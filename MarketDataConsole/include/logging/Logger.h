#ifndef Logger_H
#define Logger_H

#include <chrono>
#include <format>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <string_view>
#include <filesystem>

class Logger
{
public:
    static void init(const std::string& path)
    {
        const std::filesystem::path logPath(path);
        if (logPath.has_parent_path()) {
            std::filesystem::create_directories(logPath.parent_path());
        }
        instance().file_.open(path, std::ios::app);
    }

    template <typename... Args>
    static void info(std::format_string<Args...> fmt, Args&&... args)
    {
        write("INFO", std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename... Args>
    static void error(std::format_string<Args...> fmt, Args&&... args)
    {
        write("ERROR", std::format(fmt, std::forward<Args>(args)...));
    }

private:
    static Logger& instance()
    {
        static Logger logger;
        return logger;
    }

    static void write(std::string_view level, const std::string& message)
    {
        auto& logger = instance();
        const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
        const auto line = std::format("{:%F %T} [{}] {}", now, level, message);

        std::scoped_lock lock(logger.mutex_);
        std::cout << line << '\n';
        if (logger.file_) {
            logger.file_ << line << std::endl;
        }
    }

    std::mutex mutex_;
    std::ofstream file_;
};

#endif