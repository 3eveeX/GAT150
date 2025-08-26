#pragma once
#include <box2d/box2d.h>
#include <memory>

	namespace whermst {
		class Physics {
		public:
			inline b2Vec2 to_b2(const vec2& v) { return b2Vec2(v.x, v.y); }
			inline vec2 to_vec2(const b2Vec2& v) { return vec2(v.x, v.y); }

			Physics() = default;

			bool Initialize();
			void Shutdown();

			void Update(float dt);

		private:
			b2WorldId m_worldId;
		};
	}
