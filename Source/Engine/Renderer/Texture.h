#pragma once
#include "Math/Vector2.h"
#include "Resources/Resource.h"
#include <string>


struct SDL_Texture;
namespace whermst {
	class Texture : public Resource {
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& fileName, class Renderer& renderer);

		vec2 GetSize();

		friend class Renderer;
	private:
		struct SDL_Texture* _texture{ nullptr };
	};
}