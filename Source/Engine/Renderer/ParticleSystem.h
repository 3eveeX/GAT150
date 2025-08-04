#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "Renderer.h"
#include <vector>

namespace whermst {

	struct Particle {
		bool active{ false };
		float lifespan = 1.0f;

		vec2 position = vec2{ 0.0f, 0.0f };
		vec2 velocity = vec2{ 0.0f, 0.0f };
		vec3 colour = vec3{ 1.0f, 1.0f, 1.0f };
	};

	class ParticleSystem {
	public:
		ParticleSystem() = default;

		bool Initialize(int poolSize = 1000);
		void Shutdown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);
	private:
		Particle* GetFreeParticle();

	private:
		std::vector<Particle> _particles;

	};
}
