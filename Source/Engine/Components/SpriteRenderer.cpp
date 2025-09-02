#include "EnginePCH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Engine.h"


namespace whermst {
	FACTORY_REGISTER(SpriteRenderer)

		void SpriteRenderer::Start()
	{
		if (!_texture && !textureName.empty()) {
			_texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
		}
	}
	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		if (_texture) {
			if (textureRect.w > 0 && textureRect.h > 0) {
				renderer.DrawTexture(*_texture,
					textureRect,
					owner->transform.position.x,
					owner->transform.position.y,
					owner->transform.rotation,
					owner->transform.scale);
			} 
			else{
			renderer.DrawTexture(*_texture,
				owner->transform.position.x,
				owner->transform.position.y,
				owner->transform.rotation,
				owner->transform.scale);
		}
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
