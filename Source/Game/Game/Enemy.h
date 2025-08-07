#pragma once
#include "Framework/Actor.h"

class Enemy : public whermst::Actor {
public:
	float speed = 200;
	float fireTime = 0.2f;
	float fireTimer = 0.2f;
	int hitPoints = 1; // Number of hits before destruction
public:
	Enemy() = default;
	Enemy(const whermst::Transform& transform, whermst::res_t<whermst::Texture> texture) :
		Actor{ transform, texture }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

};

