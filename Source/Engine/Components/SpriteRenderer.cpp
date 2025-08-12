#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
namespace whermst {
	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		auto texture = Resources().Get<Texture>(textureName, renderer).get();
			if (texture) {
				renderer.DrawTexture(*texture,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			}
	}
	/*void SpriteRenderer::UpdateTexture(const std::string& newTextureName)
	{
		textureName = newTextureName;
		Draw(whermst::GetEngine().GetRenderer());
	}*/
}
