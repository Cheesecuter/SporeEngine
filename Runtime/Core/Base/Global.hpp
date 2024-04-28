#pragma once

#include <mutex>
#include <string>

namespace Spore
{
	extern std::mutex g_global_mutex;
	extern bool g_tick_run;
	extern bool g_tick_stop;
	extern float iTime;
	extern std::string g_terminal_output;
}
