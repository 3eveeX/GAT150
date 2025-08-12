#include "Projectile.h"
#include "Engine.h"
#include "Player.h"
#include "../GamePCH.h"

void Projectile::Update(float dt)
{
	whermst::vec2 force = whermst::vec2{ 1, 0 }.rotate(whermst::math::degToRad(transform.rotation)) * speed;
	//velocity = force;
	auto* rb = GetComponent<whermst::Rigidbody>();
	if (rb) {
		rb->velocity = force;
	}

	transform.position.x = whermst::math::wrap(transform.position.x, 0.0f, (float)whermst::GetEngine().GetRenderer().GetWidth());
	transform.position.y = whermst::math::wrap(transform.position.y, 0.0f, (float)whermst::GetEngine().GetRenderer().GetHeight());

	whermst::Particle particle;
	particle.position = transform.position;
	particle.velocity = whermst::random::onUnitCircle() * whermst::random::getReal(10.0f, 200.0f);
	if (whermst::tolower(tag) == whermst::tolower("enemy")){
		particle.colour = whermst::vec3{ 1.0f, 0, 0 };
}															
	else {
		particle.colour = whermst::vec3{ 0, 1.0f, 0 };
	}
	particle.lifespan = 0.2f;
	particle.active = true;
	whermst::GetEngine().GetPT().AddParticle(particle);
	Actor::Update(dt);
}

void Projectile::OnCollision(Actor* other)
{
	if (whermst::tolower(other->tag) != whermst::tolower(tag)) {
		destroyed = true;
	}
}
