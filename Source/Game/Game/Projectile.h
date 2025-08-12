#pragma once
#include "Framework/Actor.h"


class Projectile : public whermst::Actor {
public:
	float speed = 200;
public:
	Projectile() = default;
	Projectile(const whermst::Transform& transform) :
		Actor{ transform }
	{}

	void Update(float dt) override;


	// Inherited via Actor
	void OnCollision(Actor* other) override;

};