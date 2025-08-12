#pragma once
#include "Collider.h"

namespace whermst{
	class CircleCollider2d : public ColliderComponent {
	public:
		float radius;

		void Update(float dt) override;
		bool CheckCollision(ColliderComponent& other) override;
	};
}
