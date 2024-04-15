#pragma once

#include <Types.hpp>

namespace Spore
{
	class Model;

	class ModelObserver
	{
	public:
		virtual ~ModelObserver();
		virtual void OnModelDeleted(Model* p_model);
	};
}