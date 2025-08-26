#pragma once

namespace whermst {
	class ICollidable {
	public:
		virtual ~ICollidable() = default;

		virtual void OnCollision(whermst::Actor* other) = 0;
	};
}