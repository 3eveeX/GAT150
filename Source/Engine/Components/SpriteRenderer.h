#pragma once
#include "RendererComponent.h"

namespace whermst
{

	

	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName; 
		rect textureRect;
		res_t<Texture> _texture;

	public:
		CLASS_PROTOTYPE(SpriteRenderer)

		void Start() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
		//void UpdateTexture(const std::string& newTextureName);
		void Read(const json::value_t& value) override;
	};
}
