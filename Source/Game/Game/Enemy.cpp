#include "Enemy.h"
#include "GameData.h"
#include "Projectile.h"
#include "Player.h"
#include "Framework/Actor.h"
#include "../GamePCH.h"

FACTORY_REGISTER(Enemy);

void Enemy::Start()
{
	whermst::EventManager::Instance().AddObserver("PlayerDead", *this);
	_rigidBody = owner->GetComponent<whermst::Rigidbody>();
	fireTimer = fireTime;
}

void Enemy::Update(float dt)
{
	

	Player* player = owner->_scene->GetActorByName<Player>("Player");
	if (player) {
		whermst::vec2 direction{ 0, 0 };
		direction = player->owner->transform.position - owner->transform.position;


		direction.Normalized();
		whermst::vec2 forward = whermst::vec2{ 1, 0 }.rotate(whermst::math::degToRad(owner->transform.rotation));
		float angle = whermst::vec2::SignedAngleBetween(forward, direction);
		owner->transform.rotation += whermst::math::radToDeg(angle * dt);
	}
	
	whermst::vec2 force = whermst::vec2{1, 0}.rotate(whermst::math::degToRad(owner->transform.rotation)) * speed;
	//velocity += force * dt;
	if (_rigidBody) {
		_rigidBody->velocity += force * dt;
	}
	
	owner->transform.position.x = whermst::math::wrap(owner->transform.position.x, 0.0f, (float)whermst::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = whermst::math::wrap(owner->transform.position.y, 0.0f, (float)whermst::GetEngine().GetRenderer().GetHeight());
	 
	fireTimer -= dt;
	if (fireTimer <= 0) {
		fireTimer = fireTime;
        whermst::Transform projectileTransform{ this->owner->transform.position, this->owner->transform.rotation, 0.5f };
        auto projectile = whermst::Instantiate<whermst::Actor>("EnemyProjectile");
		projectile->transform = projectileTransform;
		projectile->Actor::GetComponent<whermst::Rigidbody>()->velocity = whermst::vec2{ 1, 0 }.rotate(whermst::math::degToRad(owner->transform.rotation)) * projectile->Actor::GetComponent<Projectile>()->speed;

        owner->_scene->AddActor(std::move(projectile), true);
		
	}
}

void Enemy::OnCollision(whermst::Actor* other)
{
	if (whermst::tolower(other->tag) != whermst::tolower(owner->tag)) {
		owner->RemoveComponent(owner->GetComponent<whermst::SpriteRenderer>());
		auto spriteRenderer = std::make_unique<whermst::SpriteRenderer>();
		if (hitPoints > 0) {
			whermst::GetEngine().GetAudio().PlaySound("enemyHit");
			if (other->name == "Player") {
				hitPoints = 0;
			}
			else {
				hitPoints--;
			}
		}

		
		if (hitPoints == 2) {
			spriteRenderer->textureName = "enemy-2life.png";
			fireTime = 2.0f;
			speed = 1.0f + whermst::random::getReal(1.0f, 2.0f) * 50.0f;
			owner->AddComponent(std::move(spriteRenderer));
		}
		else if (hitPoints == 1) {
			spriteRenderer->textureName = "enemy-1life.png";
			fireTime = 4.0f;
			speed = 1.0f + whermst::random::getReal(1.0f, 2.0f) * 10.0f;
			owner->AddComponent(std::move(spriteRenderer));
		}


		if(hitPoints == 0){
		whermst::GetEngine().GetAudio().PlaySound("Explode");
		owner -> destroyed = true;
		whermst::EventManager::Instance().Notify(whermst::Event{ "addPoints", 100 });
		for (int i = 0; i < 100; i++) {
			whermst::Particle particle;
			particle.position = owner->transform.position;
			particle.velocity = (whermst::random::onUnitCircle() * 3) * whermst::random::getReal(1.0f, 40.0f);
			int colourRandom = whermst::random::getInt() % 3;
			if (colourRandom == 0) {
				particle.colour = whermst::vec3{ 1.0f, 0, 0 }; // Red
			}
			else if (colourRandom == 1) {
				particle.colour = whermst::vec3{ 1.0, .8f, 0.1f }; // orange
			}
			else {
				particle.colour = whermst::vec3{ 1.0f, 1.0f, 0 }; // yellow
			}
			particle.lifespan = 2;
			particle.active = true;
			whermst::GetEngine().GetPT().AddParticle(particle);
		}
		}
	}
}

void Enemy::Read(const whermst::json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, speed);
	whermst::json::Read(value, "hp", hitPoints);
	JSON_READ(value, fireTime);
}

void Enemy::OnNotify(const whermst::Event& event)
{
	if(whermst::equalsIgnoreCase(event.id, "PlayerDead")) {
		owner->destroyed = true;
	}
}
