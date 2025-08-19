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

}