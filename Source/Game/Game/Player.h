#pragma once
#include "Framework/Component.h"
#include "Framework/Actor.h"


class Player : public whermst::Component, public whermst::ICollidable{
public:
	Player() = default;
	CLASS_PROTOTYPE(Player)
	

	void Update(float dt) override;

	float speed;
	float rotateRate;
	float fireTime;
	float fireTimer;

	void Start() override;

	// Inherited via Actor
	void OnCollision(class whermst::Actor* other);
	void Read(const whermst::json::value_t& value) override;

    private:  
        whermst::Rigidbody* _rigidBody; // Change from std::unique_ptr to a raw pointer
};
