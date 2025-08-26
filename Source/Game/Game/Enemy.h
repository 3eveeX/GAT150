#pragma once
#include "Framework/Component.h"
#include "Framework/Actor.h"



class Enemy : public whermst::Component, public whermst::ICollidable, public whermst::IObserver {
public:
	float speed = 200;
	float fireTime = 0.2f;
	float fireTimer = 0.2f;
	int hitPoints = 1; // Number of hits before destruction

	whermst::Rigidbody* _rigidBody{ nullptr };
public:
	Enemy() = default;
	CLASS_PROTOTYPE(Enemy)


	void Start() override;

	void Update(float dt) override;

	void OnCollision(whermst::Actor* other) override;

	void Read(const whermst::json::value_t& value) override;

	void OnNotify(const whermst::Event& event) override;
};

