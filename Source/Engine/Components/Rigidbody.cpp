#include "EnginePCH.h"
#include "Rigidbody.h"

FACTORY_REGISTER(Rigidbody)

namespace whermst {
	void Rigidbody::Update(float dt)
	{
		owner->transform.position += velocity * dt;
		velocity *= (1.0f - damping * dt);
	}
}