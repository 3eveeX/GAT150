#pragma once
#include "Vector2.h"

namespace whermst {
	struct Transform {
		vec2 position{ 0, 0 };
		float rotation = 0;
		float scale = 1;

		Transform() = default;
		Transform(const vec2& position, float rotation = 0.0f, float scale = 1.0f)
			: position(position), rotation(rotation), scale(scale) 
		{ }

		
	};
}