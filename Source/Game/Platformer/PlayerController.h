#pragma once
#include "Framework/Component.h"
#include "Framework/Actor.h"


class PlayerController : public whermst::Component, public whermst::ICollidable {
public:
	PlayerController() = default;
	CLASS_PROTOTYPE(PlayerController)


		void Update(float dt) override;

	float speed;
	float maxSpeed;
	float fireTime;
	float fireTimer;
	float jump;

	void Start() override;

	void OnCollision(class whermst::Actor* other);
	void Read(const whermst::json::value_t& value) override;

private:
	whermst::Rigidbody* _rigidBody; // Change from std::unique_ptr to a raw pointer
};

