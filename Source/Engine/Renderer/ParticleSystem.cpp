#include "ParticleSystem.h"


namespace whermst {
	bool ParticleSystem::Initialize(int poolSize) {
		_particles.resize(poolSize);

		return true;
	}

	void ParticleSystem::Shutdown() {

	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : _particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				particle.active = (particle.lifespan > 0);
				particle.position += particle.velocity * dt;
			}

		}
	}

	void ParticleSystem::Draw(class Renderer& renderer) {
		for (auto& particle : _particles) {
			if (particle.active) {
				renderer.SetColourf(particle.colour.r, particle.colour.g, particle.colour.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}

		}
	}
	void ParticleSystem::AddParticle(const Particle& particle)
	{
		Particle* pParticle = GetFreeParticle();
		if (pParticle) {
			*pParticle = particle;
			pParticle->active = true;
		}
	}
	Particle* ParticleSystem::GetFreeParticle()
	{	
		for (auto& particle : _particles) {
			if (!particle.active) {
				return &particle;
			}
		}
		return nullptr;
	}
}