#include "EnginePCH.h"
#include "MeshRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Mesh.h"


namespace whermst {
	FACTORY_REGISTER(MeshRenderer)
	void MeshRenderer::Update(float dt)
	{
		//
	}

	void MeshRenderer::Draw(Renderer& renderer)
	{
		auto mesh = Resources().Get<Mesh>(meshName);
		if (mesh) {
			mesh->Draw(renderer, owner->transform);
		}
	}

	void MeshRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, meshName);
		if (meshName.empty()) {
			Logger::Error("MeshRenderer: Mesh name is empty.");
		}
		if (!Resources().Get<Mesh>(meshName)) {
			Logger::Error("MeshRenderer: Mesh '{}' not found in resources.", meshName);
		}
	}

}