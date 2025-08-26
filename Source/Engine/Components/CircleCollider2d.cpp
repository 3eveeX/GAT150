#include "EnginePCH.h"
#include "CircleCollider2d.h"

namespace whermst
{
FACTORY_REGISTER(CircleCollider2d)
void CircleCollider2d::Update(float dt)
{
}

bool CircleCollider2d::CheckCollision(ColliderComponent& other)
{
	float distance = (owner->transform.position - other.owner->transform.position).Length();
	auto collider = dynamic_cast<CircleCollider2d*>(&other);

	if (collider) {
	 float radii = radius + collider ->radius;
	 if (distance <= radii) return true;
	}


	//float distance = (actorA->transform.position - actorB->transform.position).Length();
	//if (distance <= (actorA->GetRadius() + actorB->GetRadius())) {
	return false;
}
void CircleCollider2d::Read(const json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, radius);
}
}
