#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "Texture.h"


namespace whermst {
	class Renderer {
	public:
		Renderer() = default;

		bool Initialize();

		void CloseWindow();
		bool CreateWindow(const std::string& name, int width, int height);
		SDL_Window* GetWindow() const { return _window; }

		void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void SetColourf(float r, float g, float b, float a = 1.0f);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x1, float y1);
		void DrawTexture(Texture* texture, float x, float y);	

		void Clear();
		void Present();

		int GetWidth() const { return _width; }
		int GetHeight() const { return _height; }
	private:
		int _width{ 0 };
		int _height{ 0 };

		SDL_Window* _window = nullptr;
		SDL_Renderer* _renderer = nullptr;

		friend class Text;
		friend class Texture;
	};
}