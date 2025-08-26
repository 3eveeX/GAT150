#pragma once
#include "Framework/Component.h"

namespace whermst {
	
	class Rigidbody : public Component{
	public:
		vec2 velocity;
		float damping;
	public:
		CLASS_PROTOTYPE(Rigidbody)

		void Update(float dt) override;

		void Read(const json::value_t& value) override;
		
	};
}