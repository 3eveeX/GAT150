#include "Text.h"
#include "Core/Logger.h"


namespace whermst {
	/// <summary>
	/// Destroys the Text object and releases its associated SDL texture resource.
	/// </summary>
	Text::~Text()
	{
		if (_texture != nullptr) {
			SDL_DestroyTexture(_texture);
		}
	}

	/// <summary>
	/// Creates a text texture using the specified renderer, text string, and color.
	/// </summary>
	/// <param name="renderer">Reference to the Renderer object used for rendering the text.</param>
	/// <param name="text">The string to be rendered as text.</param>
	/// <param name="color">The color of the text, represented as a vec3 (RGB components in the range [0, 1]).</param>
	/// <returns>True if the text texture was created successfully; false otherwise.</returns>
	bool Text::Create(Renderer& renderer, const std::string& text, const vec3& color = {1, 1, 1})
	{
		SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(_font->_ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {
			Logger::Error("Could not create surface");
			return false;
		}
		_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);
		if (_texture == nullptr) {
			SDL_DestroySurface(surface);
			Logger::Error("Could not create texture: {}", SDL_GetError());
			return false;
		}

		SDL_DestroySurface(surface);

		return true;
	}

	/// <summary>
	/// Draws the text texture at the specified position using the given renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the text.</param>
	/// <param name="x">The x-coordinate where the text will be drawn.</param>
	/// <param name="y">The y-coordinate where the text will be drawn.</param>
	void Text::Draw(Renderer& renderer, float x, float y, float scale)
	{
		assert(_texture != nullptr);

		float width = 1, height = 1;
		width *= scale;
		height *= scale;
		bool success = SDL_GetTextureSize(_texture, &width, &height);
		assert(success);

		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer._renderer, _texture, NULL, &rect);
		assert(success);
	}
}
