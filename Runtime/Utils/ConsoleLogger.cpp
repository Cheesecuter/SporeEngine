#include <ConsoleLogger.hpp>
#include <SpdlogImguiSinks.h>

namespace Spore
{
	ConsoleLogger::ConsoleLogger()
	{

	}

	ConsoleLogger::~ConsoleLogger()
	{

	}

	void ConsoleLogger::InitLogger()
	{
		if (!m_logger_initialized)
		{
			m_logger = spdlog::sinks::imgui_logger_mt("Logger");
			m_logger_initialized = true;
		}
	}


	std::shared_ptr<spdlog::logger> ConsoleLogger::Logger()
	{
		return m_logger;
	}
}