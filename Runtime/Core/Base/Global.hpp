#pragma once

#include <mutex>

namespace Spore
{
	extern std::mutex g_global_mutex;
	extern bool g_tick_run;
	extern bool g_tick_stop;
	extern float iTime;
}
