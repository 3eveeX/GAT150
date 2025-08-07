#pragma once
#include "Framework/Actor.h"

class Player : public whermst::Actor{
public:
	Player() = default;
	Player(const whermst::Transform& transform, whermst::res_t<whermst::Texture> texture) :
		Actor{ transform, texture } 
	{}

	void Update(float dt) override;

	float speed = 500.0f;
	float rotateRate = 180.0f;
	float fireTime = 0.2f;
	float fireTimer = 0.2f;

	// Inherited via Actor
	void OnCollision(Actor* other) override;

};
