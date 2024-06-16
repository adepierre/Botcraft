#pragma once

#include <string>
#include <mutex>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <atomic>
#include <thread>

constexpr const char* file_name(const char* path)
{
    const char* file = path;
    while (*path)
    {
        if (*path == '\\' || *path == '/')
        {
            file = path + 1;
        }
        path += 1;
    }
    return file;
}

#define LOG(osstream, level) do { \
    Botcraft::Logger& logger = Botcraft::Logger::GetInstance(); \
    if (level < logger.GetLogLevel()) \
        break; \
    std::ostringstream logger_ostringstream; \
    logger_ostringstream << logger.GetDate().rdbuf() << ' ' << Botcraft::Logger::level_strings.at(level) \
    << " [" << logger.GetThreadName(std::this_thread::get_id()) << "(" << std::this_thread::get_id() << ")] " \
    << file_name(__FILE__) << '(' << __LINE__ << "): " << osstream << '\n'; \
    logger.Log(logger_ostringstream.str()); \
} while(0)

#define LOG_TRACE(osstream) LOG(osstream, Botcraft::LogLevel::Trace)
#define LOG_DEBUG(osstream) LOG(osstream, Botcraft::LogLevel::Debug)
#define LOG_INFO(osstream) LOG(osstream, Botcraft::LogLevel::Info)
#define LOG_WARNING(osstream) LOG(osstream, Botcraft::LogLevel::Warning)
#define LOG_ERROR(osstream) LOG(osstream, Botcraft::LogLevel::Error)
#define LOG_FATAL(osstream) LOG(osstream, Botcraft::LogLevel::Fatal)

namespace Botcraft
{
    enum class LogLevel
    {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        None
    };
    std::ostream& operator<<(std::ostream& os, const LogLevel v);

    class Logger
    {
    private:
        Logger();
    public:
        inline static const std::unordered_map<LogLevel, std::string> level_strings
        {
            { LogLevel::Trace,   "[TRACE]"},
            { LogLevel::Debug,   "[DEBUG]" },
            { LogLevel::Info,    "[INFO]" },
            { LogLevel::Warning, "[WARNING]" },
            { LogLevel::Error,   "[ERROR]" },
            { LogLevel::Fatal,   "[FATAL]" },
            { LogLevel::None,    "[]" }
        };
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;
        ~Logger();

        static Logger& GetInstance();
        void Log(const std::string& s);
        void SetFilename(const std::string& s);
        void SetLogLevel(const LogLevel l);
        LogLevel GetLogLevel() const;
        void SetLogFunc(const std::function<void(const std::string&)>& f);
        std::stringstream GetDate() const;

        /// @brief Register the current thread in the map. It will be automatically removed on thread exit.
        /// @param name Thread name
        void RegisterThread(const std::string& name);

        /// @brief Register a thread in the map. It will *NOT* be automatically removed on thread exit.
        /// @param id Thread id
        /// @param name Thread name
        void RegisterThread(const std::thread::id id, const std::string& name);

        /// @brief Get the name of a given thread
        /// @param id Thread id
        /// @return The name of the thread, "" if not in map
        std::string GetThreadName(const std::thread::id id);

        /// @brief Remove a thread from the map
        /// @param id Thread id
        void UnregisterThread(const std::thread::id id);

    private:
        std::mutex mutex;
        std::string filename;
        std::atomic<LogLevel> log_level;
        std::function<void(const std::string&)> log_func;

        std::chrono::steady_clock::time_point last_time_logged;
        std::string file_buffer;

        std::mutex thread_mutex;
        std::unordered_map<std::thread::id, std::string> thread_names;
    };
}
