#pragma once
#include "Framework/Component.h"
#include "Framework/Actor.h"



class Projectile : public whermst::Component {
public:
	float speed;
public:
	Projectile() = default;
	CLASS_PROTOTYPE(Projectile)
	

	void Update(float dt) override;


	// Inherited via Actor
	void OnCollision(whermst::Actor* other);
	void Read(const whermst::json::value_t& value) override;

};