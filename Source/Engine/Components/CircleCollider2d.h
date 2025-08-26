#pragma once
#include "Collider.h"

namespace whermst{
	class CircleCollider2d : public ColliderComponent {
	public:
		CLASS_PROTOTYPE(CircleCollider2d)
		float radius;

		void Update(float dt) override;
		bool CheckCollision(ColliderComponent& other) override;

		void Read(const json::value_t& value) override;
	};
}
