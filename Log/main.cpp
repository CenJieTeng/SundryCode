#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

int main()
{
    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
    spdlog::get("console")->info("Hello World!");
    spdlog::get("stderr")->info("Hello World!");
    spdlog::info("Hello World!");
    spdlog::error("Error Code: {}\tReason: {}", -1, "msg");

    //basic file log
    try
    {
        auto basic_logger = spdlog::basic_logger_mt("basic_logger", "logs/log.txt");
        spdlog::get("basic_logger")->info("Hello World!");
    }
    catch(const spdlog::spdlog_ex &ex)
    {
        std::cerr << ex.what() << '\n';
    }

    return 0;
}