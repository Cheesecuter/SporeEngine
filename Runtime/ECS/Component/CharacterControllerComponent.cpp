#include <CharacterControllerComponent.hpp>
#include <Window.hpp>
#include <Keyboard.hpp>
#include <TransformComponent.hpp>
#include <PhysicsComponent.hpp>
#include <Object.hpp>

namespace Spore
{
	CharacterControllerComponent::CharacterControllerComponent()
	{
		m_name = "CharacterController";
	}

	CharacterControllerComponent::~CharacterControllerComponent()
	{

	}

	void CharacterControllerComponent::InspectorPanel()
	{
		if (ImGui::CollapsingHeader(m_name.c_str(), true))
		{
			ImGui::Text("Character controller");
		}
	}

	void CharacterControllerComponent::Tick(float32 p_delta_time)
	{
		bool isKeyPressed = false;
		PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(GetReferencedObject()->GetComponent("Physics"));
		if (g_tick_run && physicsComponent != nullptr)
		{
			vec3f linearVelocityTemp = physicsComponent->GetLinearVelocity();
			if (Keyboard::GetInstance().GetKey(nullptr) == KEY_W)
			{
				linearVelocityTemp.z -= 1.0f;
				if (linearVelocityTemp.z <= -3.0f)
					linearVelocityTemp.z = -3.0f;
				isKeyPressed = true;
			}
			if (Keyboard::GetInstance().GetKey(nullptr) == KEY_S)
			{
				linearVelocityTemp.z += 1.0f;
				if (linearVelocityTemp.z >= 3.0f)
					linearVelocityTemp.z = 3.0f;
				isKeyPressed = true;
			}
			if (Keyboard::GetInstance().GetKey(nullptr) == KEY_A)
			{
				linearVelocityTemp.x -= 1.0f;
				if (linearVelocityTemp.x <= -3.0f)
					linearVelocityTemp.x = -3.0f;
				isKeyPressed = true;
			}
			if (Keyboard::GetInstance().GetKey(nullptr) == KEY_D)
			{
				linearVelocityTemp.x += 1.0f;
				if (linearVelocityTemp.x >= 3.0f)
					linearVelocityTemp.x = 3.0f;
				isKeyPressed = true;
			}
			if (isKeyPressed)
			{
				physicsComponent->SetLinearVelocity(linearVelocityTemp);
				physicsComponent->Wake();
			}
		}
	}
}