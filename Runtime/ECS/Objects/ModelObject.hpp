#pragma once
#ifndef MODEL_OBJECT_HPP
#define MODEL_OBJECT_HPP

#include <Types.hpp>
#include <Object.hpp>
#include <Model.hpp>

namespace Spore
{
	class ModelObject : public Object
	{
	public:
		ModelObject(const std::string& identifier_p);
		~ModelObject();

		std::map<std::string, Model*> modelMapper;
		uint32 VAO, VBO, EBO;

		void AddModel(Model* model_p);
		void DeleteModel(Model model_p);
		void DeleteModel(std::string identifier_p);
		void OnModelDeleted(Model* model) override;
		void Render(std::vector<Shader*> shaders_p, Camera* camera_p,
					uint32 scrWidth_p, uint32 scrHeight_p,
					mat4f projection_p, mat4f view_p, mat4f model_p) override;

	protected:

	private:

	};
}

#endif
