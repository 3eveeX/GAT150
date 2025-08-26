#pragma once
#include "Framework/Component.h"
#include "Framework/Actor.h"


class Player : public whermst::Component{
public:
	Player() = default;
	CLASS_PROTOTYPE(Player)
	

	void Update(float dt) override;

	float speed;
	float rotateRate;
	float fireTime;
	float fireTimer;



	// Inherited via Actor
	void OnCollision(class whermst::Actor* other);
	void Read(const whermst::json::value_t& value) override;
};
