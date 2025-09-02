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
		_rigidBody->ApplyForce(whermst::vec2{ 1, 0 }* dir * 1000);
	}

 if(whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) || whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_W) || whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_UP)) {
		_rigidBody->ApplyForce(whermst::vec2{ 0, -1 } * 1000 * jump);
 }
}  

void PlayerController::Start()  
{ 
	_rigidBody = owner->GetComponent<whermst::Rigidbody>();
}  

void PlayerController::OnCollision(class whermst::Actor* other)
{

}

void PlayerController::Read(const whermst::json::value_t& value)  
{ 
	Object::Read(value);
	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, fireTime);
	JSON_READ(value, jump);
}
