#pragma once
#include "Framework/Actor.h"

class Player : public whermst::Actor{
public:
	Player() = default;
	Player(const whermst::Transform& transform, std::shared_ptr<class whermst::Model> model) :
		Actor{ transform, model } 
	{}

	void Update(float dt) override;

	float speed = 500.0f;
	float rotateRate = 180.0f;
	float fireTime = 0.2f;
	float fireTimer = 0.2f;

	// Inherited via Actor
	void OnCollision(Actor* other) override;

};
