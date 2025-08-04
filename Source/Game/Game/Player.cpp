#include "Player.h"
#include "Engine.h"
#include "GameData.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"
#include "Math/Vector3.h"
#include "Projectile.h"
#include "Framework/Scene.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "SpaceGame.h"
#include "Core/Random.h"

void Player::Update(float dt)
{
    
    whermst::Particle particle;
    particle.position = transform.position;
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

	transform.rotation += (rotate * rotateRate) * dt;

    whermst::vec2 direction{ 1, 0 };
	whermst::vec2 force = direction.rotate(whermst::math::degToRad(transform.rotation)) * thrust * speed;

	 velocity += force * dt;

   
     transform.position.x = whermst::math::wrap(transform.position.x, 0.0f, (float)whermst::GetEngine().GetRenderer().GetWidth());
     transform.position.y = whermst::math::wrap(transform.position.y, 0.0f, (float)whermst::GetEngine().GetRenderer().GetHeight());
	 
     fireTimer -= dt;
     if (fireTimer <= 0.0f && whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		 whermst::GetEngine().GetAudio().PlaySound("laser");
		 fireTimer = fireTime;
         std::shared_ptr<whermst::Model> model = std::make_shared<whermst::Model>(GameData::projectilePoints, whermst::vec3{ 1.0f, 0.9f, 0.0f });
         whermst::Transform transform{this -> transform.position, this -> transform.rotation, 2.0f};
         auto projectile = std::make_unique<Projectile>(transform, model);
         projectile->speed = 1000.0f;
         projectile->lifespan = 1.5f;
         projectile->name = "Projectile";
         projectile->tag = "player";
         _scene->AddActor(std::move(projectile));
     }
    
     Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
    if (whermst::tolower(other->tag) != whermst::tolower(tag)) {
		whermst::GetEngine().GetAudio().PlaySound("playerdeath");
        destroyed = true;
        dynamic_cast<SpaceGame*>(_scene->GetGame())->OnPlayerDeath();
    }

}
