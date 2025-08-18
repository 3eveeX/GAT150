#pragma once
#include "Framework/Component.h"



class Enemy : public whermst::Component {
public:
	float speed = 200;
	float fireTime = 0.2f;
	float fireTimer = 0.2f;
	int hitPoints = 1; // Number of hits before destruction
public:
	Enemy() = default;
	/*Enemy(const whermst::Transform& transform) :
		Actor{ transform}
	{
	}*/

	/*void UpdateTexture(whermst::res_t<whermst::Texture> texture) {
		_texture = texture;
	}*/

	void Update(float dt) override;

	void OnCollision(class Actor* other);

};

