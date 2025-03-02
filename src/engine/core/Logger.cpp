#include "Logger.hpp"
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>


void Logger::Init()
{
}


void Logger::AddLogger(std::string name, std::string pattern, spdlog::level::level_enum log_level, std::string file)
{
    if (!m_Loggers.contains(name)) {
        if (file == "CONSOLE") {
            m_Loggers[name] = spdlog::stdout_color_mt(name);
        }
        else if (file == "ERROR") {
            m_Loggers[name] = spdlog::stderr_color_mt(name);
        }
        else {
            m_Loggers[name] = spdlog::basic_logger_mt(name, file);
        }
        m_Loggers[name]->set_pattern(pattern);
        m_Loggers[name]->set_level(log_level);
    }
}

void Logger::RemoveLogger(std::string name)
{
    if (m_Loggers.contains(name)) {
        m_Loggers.erase(name);
    }
}

std::shared_ptr<spdlog::logger> Logger::GetLogger(std::string name)
{
    assert(name != "");
    if (m_Loggers.contains(name)) {
        return m_Loggers[name];
    }
    //return nullptr;
}

bool Logger::IsValidLog(std::string name)
{
    if (m_Loggers.contains(name)) {
        return true;
    }
    return false;
}
