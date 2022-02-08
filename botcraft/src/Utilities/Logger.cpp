#include "botcraft/Utilities/Logger.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace Botcraft
{
    Logger::Logger()
    {
        filename = "";
        file_buffer = "";
        log_level = LogLevel::Info;
        last_time_logged = std::chrono::steady_clock::now();
        log_func = [this](const std::string& s)
        {
            std::cout << s;
            std::cout.flush();
        };
    }

    Logger::~Logger()
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (filename != "")
        {
            std::ofstream outfile(filename, std::ios::out | std::ios::app);
            outfile << file_buffer;
        }
        file_buffer = "";
    }

    Logger& Logger::GetInstance()
    {
        static Logger test;
        return test;
    }

    void Logger::Log(const std::string& s)
    {
        std::lock_guard<std::mutex> lock(mutex);
        log_func(s);

        file_buffer += s;
        auto now = std::chrono::steady_clock::now();
        // Only write to file every 5 seconds
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time_logged).count() > 5000)
        {
            if (filename != "")
            {
                std::ofstream outfile(filename, std::ios::out | std::ios::app);
                outfile << file_buffer;
            }
            file_buffer = "";
            last_time_logged = now;
        }
    }

    void Logger::SetFilename(const std::string& s)
    {
        std::lock_guard<std::mutex> lock(mutex);
        filename = s;
    }

    void Logger::SetLogLevel(const LogLevel l)
    {
        log_level = l;
    }

    LogLevel Logger::GetLogLevel() const
    {
        return log_level;
    }

    void Logger::SetLogFunc(const std::function<void(const std::string&)>& f)
    {
        std::lock_guard<std::mutex> lock(mutex);
        log_func = f;
    }

    std::stringstream Logger::GetDate() const
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm;
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif

        std::stringstream s;
        s << '[' << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << ms.count() << ']';

        return s;
    }

    void Logger::RegisterThread(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(thread_mutex);
        thread_names[std::this_thread::get_id()] = name;

        thread_local struct ThreadExiter
        {
            ~ThreadExiter()
            {
                Logger::GetInstance().UnregisterThread(std::this_thread::get_id());
            }
        } exiter;
    }

    void Logger::RegisterThread(const std::thread::id id, const std::string& name)
    {
        std::lock_guard<std::mutex> lock(thread_mutex);
        thread_names[id] = name;
    }

    std::string Logger::GetThreadName(const std::thread::id id)
    {
        std::lock_guard<std::mutex> lock(thread_mutex);
        return thread_names[id];
    }

    void Logger::UnregisterThread(const std::thread::id id)
    {
        std::lock_guard<std::mutex> lock(thread_mutex);
        thread_names.erase(id);
    }
}
