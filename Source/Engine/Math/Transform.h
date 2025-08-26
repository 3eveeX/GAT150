#pragma once
#include "Vector2.h"
#include "Core/Serializable.h"

namespace whermst {
	struct Transform : public ISerializable{
		vec2 position{ 0, 0 };
		float rotation = 0;
		float scale = 1;

		Transform() = default;
		Transform(const vec2& position, float rotation = 0.0f, float scale = 1.0f)
			: position(position), rotation(rotation), scale(scale) 
		{ }

		void Read(const json::value_t& value) override;
		
	};
}