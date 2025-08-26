#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Engine.h"


namespace whermst {
	FACTORY_REGISTER(SpriteRenderer)

		void SpriteRenderer::Start()
	{
		_texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
	}
	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
			if (_texture) {
				renderer.DrawTexture(*_texture,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			}
	}
	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, textureName);
	}
	/*void SpriteRenderer::UpdateTexture(const std::string& newTextureName)
	{
		textureName = newTextureName;
		Draw(whermst::GetEngine().GetRenderer());
	}*/
}
