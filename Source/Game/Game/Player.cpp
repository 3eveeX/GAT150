#include "Player.h"
#include "GameData.h"
#include "Projectile.h"
#include "Framework/Actor.h" // Add this include to ensure the Actor class is fully defined before use.
#include "SpaceGame.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Player);

void Player::Update(float dt)
{
   
    whermst::Particle particle;
    particle.position = owner->transform.position;
    particle.velocity = whermst::vec2{ whermst::random::getReal(-5.0f, 5.0f), 0};
    particle.colour = whermst::vec3{ 1.0f, 1.0f, 1.0f };
    particle.lifespan = 2;
    particle.active = true;
    whermst::GetEngine().GetPT().AddParticle(particle);

	float thrust = 0;

    float rotate = 0;
    if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

    if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = 1; 
    if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	owner->transform.rotation += (rotate * rotateRate) * dt;

    whermst::vec2 direction{ 1, 0 };
	whermst::vec2 force = direction.rotate(whermst::math::degToRad(owner->transform.rotation)) * thrust * speed;

	 //velocity += force * dt;
	auto* rb = owner->GetComponent<whermst::Rigidbody>();
	if (rb) {
		rb->velocity += force * dt;
	}
   
     owner->transform.position.x = whermst::math::wrap(owner->transform.position.x, 0.0f, (float)whermst::GetEngine().GetRenderer().GetWidth());
     owner->transform.position.y = whermst::math::wrap(owner->transform.position.y, 0.0f, (float)whermst::GetEngine().GetRenderer().GetHeight());
     fireTimer -= dt;
     if (fireTimer <= 0.0f && whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
         whermst::GetEngine().GetAudio().PlaySound(*(whermst::Resources().Get<whermst::AudioClip>("Laser.mp3", whermst::GetEngine().GetAudio())));
	 
         fireTimer = fireTime;
         
         whermst::Transform Transform{this -> owner->transform.position, this -> owner->transform.rotation, 1.0f};
         auto projectile = whermst::Instantiate<whermst::Actor>("PlayerProjectile"); 

         projectile->transform = Transform;
		 projectile->Actor::GetComponent<whermst::Rigidbody>()->velocity = whermst::vec2{ 1, 0 }.rotate(whermst::math::degToRad(owner->transform.rotation)) * projectile->Actor::GetComponent<Projectile>()->speed;

         owner->_scene->AddActor(std::move(projectile), true);
     }
    }

void Player::OnCollision(whermst::Actor* other)
{
    if (whermst::tolower(other->tag) != whermst::tolower(owner->tag)) {
        whermst::GetEngine().GetAudio().PlaySound("playerdeath");
        owner->destroyed = true;
        dynamic_cast<SpaceGame*>(owner->_scene->GetGame())->OnPlayerDeath();
    }
}

void Player::Read(const whermst::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, speed);
	JSON_READ(value, rotateRate);
	JSON_READ(value, fireTime);
}
