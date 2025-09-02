#pragma once
#include "Framework/Component.h"

namespace whermst {
	
	class Rigidbody : public Component{
	public:
		PhysicsBody::PhysicsBodyDef bodyDef;
		vec2 size{ 0, 0 };
		vec2 scale{ 1, 1 };

		vec2 velocity{ 0, 0 };
		float damping{ 0 };
	public:
		Rigidbody() = default;
		Rigidbody(const Rigidbody& other);

		CLASS_PROTOTYPE(Rigidbody)

		void Start() override;

		void Update(float dt) override;

		void Read(const json::value_t& value) override;

		void ApplyForce(const vec2& force);
		void ApplyTorque(float radians);
		void setVelocity(const vec2& velocity);

	private:
		std::unique_ptr<PhysicsBody> _body;
		
	};
}