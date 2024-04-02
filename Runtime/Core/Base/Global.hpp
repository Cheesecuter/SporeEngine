#pragma once
#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <mutex>

namespace Spore
{
	extern std::mutex g_global_mutex;
}

#endif
