#pragma once

namespace Spore
{
#ifndef ST_MODEL_TYPE
#define ST_MODEL_TYPE
	enum class ModelType
	{
		CUBE,
		SPHERE,
		CAPSULE,
		CYLINDER,
		PLANE,
		QUAD,
		CUSTOM,
		CUSTOM_CUBE,
		NONE,
		CUSTOM_FLOOR,
		CUSTOM_WALL
	};
#endif
}