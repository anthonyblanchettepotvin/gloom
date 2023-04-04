#include "ImGuiActorAdapter.h"

#include "../../components/TransformComponent.h"
#include "../../components/ModelRendererComponent.h"
#include "../../components/SpriteRendererComponent.h"
#include "../../components/PointLightComponent.h"
#include "../../components/DirectionalLightComponent.h"
#include "../../imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

ImGuiActorAdapter::ImGuiActorAdapter(Actor* actor) : UiActorAdapter(actor)
{
}

void ImGuiActorAdapter::RenderUi()
{
	if (actor)
	{
		ImGui::Text(actor->GetName().c_str());

		TransformComponent* transformComponent = actor->FindComponentByType<TransformComponent>();
		if (transformComponent)
		{
			ImGui::Separator();
			ImGui::InputFloat3("Position", glm::value_ptr(transformComponent->GetPositionReference()));
			ImGui::InputFloat3("Scale", glm::value_ptr(transformComponent->GetScaleReference()));
			ImGui::InputFloat3("Rotation", glm::value_ptr(transformComponent->GetRotationReference()));
		}

		ModelRendererComponent* modelRendererComponent = actor->FindComponentByType<ModelRendererComponent>();
		if (modelRendererComponent)
		{
			ImGui::Separator();
			ImGui::Text(modelRendererComponent->GetModel()->GetPath().c_str());
			ImGui::Text(modelRendererComponent->GetShader()->GetVertexShaderPath().c_str());
			ImGui::Text(modelRendererComponent->GetShader()->GetFragmentShaderPath().c_str());
		}

		SpriteRendererComponent* spriteRendererComponent = actor->FindComponentByType<SpriteRendererComponent>();
		if (spriteRendererComponent)
		{
			ImGui::Separator();
			ImGui::Text(spriteRendererComponent->GetSprite()->GetTexture()->GetPath().c_str());
			ImGui::Text(spriteRendererComponent->GetShader()->GetVertexShaderPath().c_str());
			ImGui::Text(spriteRendererComponent->GetShader()->GetFragmentShaderPath().c_str());
		}

		PointLightComponent* pointLightComponent = actor->FindComponentByType<PointLightComponent>();
		if (pointLightComponent)
		{
			ImGui::Separator();
			ImGui::SliderFloat3("Ambient Color", glm::value_ptr(pointLightComponent->GetAmbientColorReference()), 0.0f, 1.0f);
			ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(pointLightComponent->GetDiffuseColorReference()), 0.0f, 1.0f);
			ImGui::SliderFloat3("Specular Color", glm::value_ptr(pointLightComponent->GetSpecularColorReference()), 0.0f, 1.0f);
			ImGui::SliderFloat("Constant", &pointLightComponent->GetLightAttenuationReference().constant, 0.0f, 2.0f);
			ImGui::SliderFloat("Linear", &pointLightComponent->GetLightAttenuationReference().linear, 0.0f, 2.0f);
			ImGui::SliderFloat("Quadratic", &pointLightComponent->GetLightAttenuationReference().quadratic, 0.0f, 2.0f);
		}

		DirectionalLightComponent* directionalLightComponent = actor->FindComponentByType<DirectionalLightComponent>();
		if (directionalLightComponent)
		{
			ImGui::Separator();
			ImGui::InputFloat3("Direction", glm::value_ptr(directionalLightComponent->GetDirectionReference()));
			ImGui::SliderFloat3("Ambient Color", glm::value_ptr(directionalLightComponent->GetAmbientColorReference()), 0.0f, 1.0f);
			ImGui::SliderFloat3("Diffuse Color", glm::value_ptr(directionalLightComponent->GetDiffuseColorReference()), 0.0f, 1.0f);
			ImGui::SliderFloat3("Specular Color", glm::value_ptr(directionalLightComponent->GetSpecularColorReference()), 0.0f, 1.0f);
		}
	}
}
