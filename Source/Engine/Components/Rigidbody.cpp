#include "EnginePCH.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
#include "Engine.h"


namespace whermst {
	FACTORY_REGISTER(Rigidbody)
		Rigidbody::Rigidbody(const Rigidbody& other)
	{
		bodyDef = other.bodyDef;
		size = other.size;
		if (other._body) {
			_body = std::make_unique<PhysicsBody>(*other._body);
		}
	}
	void Rigidbody::Start()
	{
		bodyDef.actor = owner;
		if(size.x == 0 && size.y == 0){
			auto spriteRenderer = owner->GetComponent<class SpriteRenderer>();
			if(spriteRenderer){
				size = spriteRenderer->_texture->GetSize();
			}
		}

		_body = std::make_unique<PhysicsBody>(owner->transform, size * scale, bodyDef, GetEngine().GetPhysics());
	}
	void Rigidbody::Update(float dt)
	{
		owner->transform.position = _body->GetPosition();
		owner->transform.rotation = math::radToDeg(_body->GetRotation());
		velocity = _body->GetVelocity();
		//owner->transform.position += velocity * dt;
		//velocity *= (1.0f - damping * dt);
	}
	void Rigidbody::ApplyForce(const vec2& force)
	{
		_body->ApplyForce(force);
	}

	void Rigidbody::ApplyTorque(float radians)
	{
		_body->ApplyTorque(radians);
	}
	void Rigidbody::setVelocity(const vec2& velocity)
	{
		_body->SetLinearVelocity(velocity);
	}
	void Rigidbody::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, size);
		JSON_READ(value, scale);


		JSON_READ_NAME(value, "gravityScale", bodyDef.gravityScale);
		JSON_READ_NAME(value, "linearDamping", bodyDef.linearDamping);
		JSON_READ_NAME(value, "angularDamping", bodyDef.angularDamping);
		JSON_READ_NAME(value, "constrainAngle", bodyDef.constrainAngle);
		JSON_READ_NAME(value, "isDynamic", bodyDef.isDynamic);
		JSON_READ_NAME(value, "friction", bodyDef.friction);
		JSON_READ_NAME(value, "restitution", bodyDef.restitution);
		JSON_READ_NAME(value, "density", bodyDef.density);
		JSON_READ_NAME(value, "isSensor", bodyDef.isSensor);

		std::string shapeName;
		JSON_READ_NAME(value, "shape", shapeName);

		if (!shapeName.empty()) {
			if (equalsIgnoreCase(shapeName, "box")) bodyDef.shape = PhysicsBody::Shape::Box;
			else if (equalsIgnoreCase(shapeName, "capsule")) bodyDef.shape = PhysicsBody::Shape::Capsule;
			else if (equalsIgnoreCase(shapeName, "circle")) bodyDef.shape = PhysicsBody::Shape::Circle;
		}
		
	}

}