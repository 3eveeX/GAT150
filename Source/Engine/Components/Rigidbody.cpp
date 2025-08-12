#include "EnginePCH.h"
#include "Rigidbody.h"

namespace whermst {
	void Rigidbody::Update(float dt)
	{
		owner->transform.position += velocity * dt;
		velocity *= (1.0f - damping * dt);
	}
}