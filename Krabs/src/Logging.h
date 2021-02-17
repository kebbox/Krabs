#pragma once

#include "spdlog/spdlog.h"



class Logging
{
private:
	static std::shared_ptr<spdlog::logger> AppLogger;
public:
	static void OnInit();
	inline static std::shared_ptr<spdlog::logger> &getAppLogger() { return AppLogger; };
};

//logging macros
#ifdef _DEBUG
#define KRABS_TRACE(...) Logging::getAppLogger()->trace(__VA_ARGS__)
#define KRABS_INFO(...)  Logging::getAppLogger()->info(__VA_ARGS__)
#define KRABS_WARN(...)  Logging::getAppLogger()->warn(__VA_ARGS__)
#define KRABS_ERROR(...) Logging::getAppLogger()->error(__VA_ARGS__)
#define KRABS_FATAL(...) Logging::getAppLogger()->fatal(__VA_ARGS__)
\
#elif _NDEBUG
#define KRABS_TRACE
#define KRABS_INFO(...)  Logging::getAppLogger()->info(__VA_ARGS__)
#define KRABS_WARN(...)  Logging::getAppLogger()->warn(__VA_ARGS__)
#define KRABS_ERROR(...) Logging::getAppLogger()->error(__VA_ARGS__)
#define KRABS_FATAL(...) Logging::getAppLogger()->fatal(__VA_ARGS__)
#endif

