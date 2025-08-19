#pragma once
#include "EnginePCH.h"
#include <memory>
#include <string>
#include "Math/Transform.h"
#include "Renderer/Texture.h"
#include "Framework/Object.h"
#include "Framework/Component.h"


namespace whermst {
	class Actor : public Object{
	public:
		std::shared_ptr<Texture> _texture{ nullptr };
		std::string tag;
		bool destroyed{ false };
		float lifespan{ 0.0f };
		Transform transform;
		class Scene* _scene{ nullptr };
	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) {}

		

		void AddComponent(std::unique_ptr<Component> component);
		void RemoveComponent(Component* component) {
			_components.erase(std::remove_if(_components.begin(), _components.end(),
				[component](const std::unique_ptr<Component>& c) { return c.get() == component; }), _components.end());
		}

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

		void Read(const json::value_t& value) override;
	protected:
		std::vector<std::unique_ptr<Component>> _components;
		//std::shared_ptr<class Model> _model;
		

	};


	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : _components) {
			if (auto castedComponent = dynamic_cast<T*>(component.get())) {
				return castedComponent;
			}
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> components;
		for (auto& component : _components) {
			if (auto castedComponent = dynamic_cast<T*>(component.get())) {
				components.push_back(castedComponent);
			}
		}
		return components;
	}
}