#pragma once
#include "Framework/Component.h"

namespace whermst {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;
	};
} // namespace whermst