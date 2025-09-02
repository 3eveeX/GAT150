#include "Physics.h"

namespace whermst {
	float Physics::s_pixelsPerMeter = 48.0f;

	bool Physics::Initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
		_worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::Shutdown() {
		b2DestroyWorld(_worldId);
	}

	void Physics::Update(float dt) {
		b2World_Step(_worldId, 1.0f / 60.0f, 4);
	}
}