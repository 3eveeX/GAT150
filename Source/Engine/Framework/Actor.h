#pragma once
#include <memory>
#include <string>
#include "../Math/Transform.h"


namespace whermst {
	class Actor {
	public:
		std::string name;
		std::string tag;
		bool destroyed{ false };
		float lifespan{ 0.0f };
		vec2 velocity{ 0, 0 };
		float damping{ 0.1f };
		Transform transform;
		class Scene* _scene{ nullptr };
	public:
		Actor() = default;
		Actor(const Transform& transform, std::shared_ptr<class Model> model) :
			transform{ transform },
			_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();


	protected:
		std::shared_ptr<class Model> _model;
		

	};
}