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
		renderer.DrawTexture(owner->_texture.get(), owner->transform.position.x, owner->transform.position.y, owner->transform.rotation, owner->transform.scale);
	}
}
