#pragma once
#include "Framework/Component.h"
#include "Framework/Actor.h"



class Projectile : public whermst::Component, public whermst::ICollidable {
public:
	float speed;
public:
	Projectile() = default;
	CLASS_PROTOTYPE(Projectile)
	

	void Update(float dt) override;


	// Inherited via Actor
	void OnCollision(whermst::Actor* other);
	void Read(const whermst::json::value_t& value) override;

	void Start() override;
private:
	whermst::Rigidbody* _rigidBody; // Change from std::unique_ptr to a raw pointer

};