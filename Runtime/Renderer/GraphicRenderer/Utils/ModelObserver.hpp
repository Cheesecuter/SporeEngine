#pragma once

namespace Spore
{
	class Model;

	class ModelObserver
	{
	public:
		ModelObserver();
		virtual ~ModelObserver();
		virtual void OnModelDeleted(Model* p_model);

	protected:

	private:

	};
}