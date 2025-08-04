#pragma once
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

namespace whermst {
	class Font {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* _ttfFont{ nullptr };
	};
}