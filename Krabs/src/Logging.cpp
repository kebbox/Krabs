#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "Krpch.h"

std::shared_ptr<spdlog::logger> Logging::AppLogger;

void Logging::OnInit()
{
	spdlog::set_pattern("%^ [%T] %n: %v%$");
	AppLogger = spdlog::stdout_color_mt("Krabs");
	AppLogger->set_level(spdlog::level::trace);
}
