#include "../GamePCH.h"  
#include "PlayerController.h" 

FACTORY_REGISTER(PlayerController);

void PlayerController::Update(float dt)  
{
	float dir = 0;
	if(whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A) || whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) {
		dir -= 1.0f;
	}
	if(whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D) || whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) {
		dir += 1.0f;
	}
	if (dir != 0) {
		_rigidBody->ApplyForce(whermst::vec2{ 1, 0 }* dir * speed);
	}

 if(whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) || whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W) || whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_UP)) {
		_rigidBody->ApplyForce(whermst::vec2{ 0, -1 } * 1000 * jump);
 }

 auto spriteRenderer = owner->GetComponent<whermst::SpriteRenderer>();
 if (spriteRenderer) {
	 if (_rigidBody->velocity.x != 0) {
		 spriteRenderer->flipH = (_rigidBody->velocity.x < 0);
	 }
 }
}  

void PlayerController::Start()  
{ 
	_rigidBody = owner->GetComponent<whermst::Rigidbody>();
}  

void PlayerController::OnCollision(class whermst::Actor* other)
{
	std::cout << "Collided with " << other->name << std::endl;
}

void PlayerController::Read(const whermst::json::value_t& value)  
{ 
	Object::Read(value);
	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, fireTime);
	JSON_READ(value, jump);
}
