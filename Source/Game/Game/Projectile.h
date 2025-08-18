#pragma once
#include "Framework/Component.h"



class Projectile : public whermst::Component {
public:
	float speed = 200;
public:
	Projectile() = default;
	/*Projectile(const whermst::Transform& transform) :
		Actor{ transform }
	{}*/

	void Update(float dt) override;


	// Inherited via Actor
	void OnCollision(class Actor* other);

};