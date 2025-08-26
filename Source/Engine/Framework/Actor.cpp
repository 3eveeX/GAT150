#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Framework/Component.h"
#include "Components/RendererComponent.h"

namespace whermst{
	FACTORY_REGISTER(Actor);

	Actor::Actor(const Actor& other) :
		Object(other),
		_texture(other._texture),
		tag(other.tag),
		lifespan(other.lifespan),
		transform(other.transform)
	{
		for(auto& component : other._components) {
			auto clonedComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clonedComponent));
		}
	}

	void Actor::Start()
	{
		for (auto& component : _components) {
			component->Start();
		}
	}

	void Actor::Destroyed()
	{
		for (auto& component : _components) {
			component->Destroyed();
		}
	}

	void Actor::Update(float dt)
	{
		if (destroyed) {
			
			return; 
		}
		if (lifespan > 0) {
			lifespan -= dt;
			if(lifespan <= 0) {
				destroyed = true;
				return;
			}
		}

		for (auto& component : _components) {
			if(component->active) component->Update(dt);
		}
		
	}

	void Actor::OnCollision(Actor* other) {
		auto collider = GetComponents<ICollidable>();
		for (auto& col : collider) {
			col->OnCollision(other);
		}
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
	
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		_components.push_back(std::move(component));
	}
	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, tag);
		JSON_READ(value, lifespan, false);
		JSON_READ(value, persistent, false);
		if (JSON_HAS(value, transform)) {
			transform.Read(JSON_GET(value, transform));
		}

		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {
				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}
	}
}