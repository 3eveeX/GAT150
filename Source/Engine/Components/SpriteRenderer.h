#pragma once
#include "RendererComponent.h"

namespace whermst
{

	

	class SpriteRenderer : public RendererComponent, Serializable {
	public:
		std::string textureName; 
	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
		//void UpdateTexture(const std::string& newTextureName);
		void Read(const json::value_t& value) override;
	};
}
