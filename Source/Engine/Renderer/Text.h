#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Math/Vector3.h"
#include <string>
#include <memory>


namespace whermst {
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<class Font> font) : _font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(Renderer& renderer, float x, float y, float scale = 1.0f);

	private:
		std::shared_ptr<Font> _font{ nullptr };
		SDL_Texture* _texture{ nullptr };
	};
}