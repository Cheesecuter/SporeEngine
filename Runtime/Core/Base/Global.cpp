#include <Global.hpp>

namespace Spore
{
	std::mutex g_global_mutex;
	bool g_tick_run = false;
	bool g_tick_stop = true;
	float iTime = 0.0f;
}