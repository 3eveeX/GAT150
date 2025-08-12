#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Framework/Component.h"
#include "Components/RendererComponent.h"

namespace whermst{


	void Actor::Update(float dt)
	{
		if (destroyed) {
			
			return; 
		}
		if (lifespan != 0.0f) {
			lifespan -= dt;
			destroyed = lifespan <= 0.0f;
		}
		for (auto& component : _components) {
			if(component->active) component->Update(dt);
		}
		transform.position += velocity * dt;
		velocity = velocity * (1.0f - damping * dt);
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;
		for (auto& component : _components) {
			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->Draw(renderer);
			}
		}


		//renderer.DrawTexture(_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	/// <summary>
	/// Returns the effective radius of the actor based on its texture size, scale, and a scaling factor.
	/// </summary>
	/// <returns>The computed radius of the actor. Returns 0 if the actor has no texture.</returns>
	float Actor::GetRadius()
	{
		if (_texture) { return (_texture->GetSize().Length() * 0.5f) * transform.scale * 1.0f; }
		else {
			Logger::Error("texture does not exist");
		}
		
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		_components.push_back(std::move(component));
	}
}