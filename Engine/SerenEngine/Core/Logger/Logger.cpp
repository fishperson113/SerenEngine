#include "Logger.h"
#include<spdlog/spdlog.h>
#include<spdlog/common.h>
namespace SerenEngine
{
	Shared<spdlog::logger> Logger::s_CoreLogger=nullptr;
	Shared<spdlog::logger> Logger::s_ClientLogger = nullptr;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%H:%M:%S] [%!:%#] [%n] [thread %t] %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("SerenEngine");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("Client");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}