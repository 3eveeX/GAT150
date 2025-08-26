#include "Projectile.h"
#include "Engine.h"
#include "Player.h"
#include "Framework/Actor.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Projectile);

void Projectile::Update(float dt)
{
	
	owner->transform.position.x = whermst::math::wrap(owner->transform.position.x, 0.0f, (float)whermst::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = whermst::math::wrap(owner->transform.position.y, 0.0f, (float)whermst::GetEngine().GetRenderer().GetHeight());

	whermst::Particle particle;
	particle.position = owner->transform.position;
	particle.velocity = whermst::random::onUnitCircle() * whermst::random::getReal(10.0f, 200.0f);
	if (whermst::tolower(owner->tag) == whermst::tolower("enemy")){
		particle.colour = whermst::vec3{ 1.0f, 0, 0 };
}															
	else {
		particle.colour = whermst::vec3{ 0, 1.0f, 0 };
	}
	particle.lifespan = 0.2f;
	particle.active = true;
	whermst::GetEngine().GetPT().AddParticle(particle);
	
	
}

void Projectile::OnCollision(whermst::Actor* other)
{
	if (whermst::tolower(other->tag) != whermst::tolower(owner->tag)) {
		owner->destroyed = true;
	}
}

void Projectile::Read(const whermst::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, speed);
}
