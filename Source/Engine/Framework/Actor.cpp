#include "Actor.h"
#include "Renderer/Model.h"

namespace whermst{


	void Actor::Update(float dt)
	{
		if (destroyed) {
			
			return; 
		}
		if (lifespan != 0.0f) {
			lifespan -= dt;
			destroyed = lifespan <= 0.0f;
		}
		transform.position += velocity * dt;
		velocity = velocity * (1.0f - damping * dt);
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;
		_model->Draw(renderer, transform);
	}
	float Actor::GetRadius()
	{
		return (_model) ? _model->GetRadius() * transform.scale * 0.8f : 0;
	}
}