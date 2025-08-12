#pragma once
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
		vec2 velocity{ 0, 0 };
		float damping{ 0.1f };
		Transform transform;
		class Scene* _scene{ nullptr };
	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		void AddComponent(std::unique_ptr<Component> component);

	protected:
		std::vector<std::unique_ptr<Component>> _components;
		//std::shared_ptr<class Model> _model;
		

	};
}