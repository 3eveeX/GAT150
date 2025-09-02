#pragma once
#include <box2d/box2d.h>
#include <memory>

	namespace whermst {
			inline b2Vec2 to_b2(const vec2& v) { return b2Vec2(v.x, v.y); }
			inline vec2 to_vec2(const b2Vec2& v) { return vec2(v.x, v.y); }
		class Physics {
		public:

			Physics() = default;

			bool Initialize();
			void Shutdown();

			void Update(float dt);

			static vec2 WorldToPixel(const vec2& world) {
				return world * s_pixelsPerMeter; 
			}
			static vec2 PixelToWorld(const vec2& pixel) {
				return pixel / s_pixelsPerMeter; 
			}

			static void SetPixelsPerMeter(float ppm) { s_pixelsPerMeter = ppm; }


			static float s_pixelsPerMeter;
		private:
			friend class PhysicsBody;
			b2WorldId _worldId;


		};
	}
