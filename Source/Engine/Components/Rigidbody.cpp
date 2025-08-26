#include "EnginePCH.h"
#include "Rigidbody.h"


namespace whermst {
	FACTORY_REGISTER(Rigidbody)
	void Rigidbody::Update(float dt)
	{
		owner->transform.position += velocity * dt;
		velocity *= (1.0f - damping * dt);
	}
	void Rigidbody::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, damping);
		JSON_READ(value, velocity);
		
	}
}