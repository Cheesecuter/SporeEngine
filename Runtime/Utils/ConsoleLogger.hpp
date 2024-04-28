#pragma once

#include <Types.hpp>
#include <SingletonInstance.hpp>

namespace Spore
{
	class ConsoleLogger : public Singleton<ConsoleLogger>
	{
	public:
		void InitLogger();
		std::shared_ptr<spdlog::logger> Logger();

	private:
		ConsoleLogger();
		~ConsoleLogger();
		friend class Singleton<ConsoleLogger>;

		std::shared_ptr<spdlog::logger> m_logger = nullptr;
		bool m_logger_initialized = false;
	};
}