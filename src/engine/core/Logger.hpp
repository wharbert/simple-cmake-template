
#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <spdlog/logger.h>
#include <unordered_map>
#include <string>


class Logger {
    public:
        void Init();
        void AddLogger(std::string name, std::string pattern, spdlog::level::level_enum log_level, std::string file = "CONSOLE");
        void RemoveLogger(std::string name);
        std::shared_ptr<spdlog::logger> GetLogger(std::string logger);
        bool IsValidLog(std::string log);

    private:
        std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> m_Loggers;
        bool zeroLogs = true;
        bool defaultLog = true;
};
