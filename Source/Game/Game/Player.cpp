#include "Player.h"
#include "GameData.h"
#include "Projectile.h"
#include "SpaceGame.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Player);

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

	 //velocity += force * dt;
	auto* rb = GetComponent<whermst::Rigidbody>();
	if (rb) {
		rb->velocity += force * dt;
	}
   
     transform.position.x = whermst::math::wrap(transform.position.x, 0.0f, (float)whermst::GetEngine().GetRenderer().GetWidth());
     transform.position.y = whermst::math::wrap(transform.position.y, 0.0f, (float)whermst::GetEngine().GetRenderer().GetHeight());
	 
     fireTimer -= dt;
     if (fireTimer <= 0.0f && whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		 //whermst::GetEngine().GetAudio().PlaySound("laser");
         whermst::GetEngine().GetAudio().PlaySound(*(whermst::Resources().Get<whermst::AudioClip>("Laser.mp3", whermst::GetEngine().GetAudio())));
         fireTimer = fireTime;
         whermst::Transform transform{this -> transform.position, this -> transform.rotation, 1.0f};
         auto projectile = std::make_unique<Projectile>(transform); // , whermst::Resources().Get<whermst::Texture>("bullet.png", whermst::GetEngine().GetRenderer()));
         projectile->speed = 1000.0f;
         projectile->lifespan = 1.5f;
         projectile->name = "Projectile";
         projectile->tag = "player";
         projectile->_texture = whermst::Resources().Get<whermst::Texture>("bullet.png", whermst::GetEngine().GetRenderer());
         auto spriteRenderer = std::make_unique<whermst::SpriteRenderer>();
         spriteRenderer->textureName = "bullet.png";
         auto rb = std::make_unique<whermst::Rigidbody>();
         auto collider = std::make_unique<whermst::CircleCollider2d>();
         collider->radius = 10;
         projectile->AddComponent(std::move(collider));
         projectile->AddComponent(std::move(rb));

         projectile->AddComponent(std::move(spriteRenderer));

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
