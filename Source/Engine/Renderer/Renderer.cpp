#include "Renderer.h"
#include <iostream>
#include "../Math/Vector2.h"
#include "Texture.h"

namespace whermst {
    bool Renderer::Initialize()
    {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error" << SDL_GetError() << std::endl;
            return false;
        }
        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    void Renderer::CloseWindow()
    {
        TTF_Quit();
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    bool Renderer::CreateWindow(const std::string& name, int width, int height)
    {
		_width = width;
		_height = height;

        _window = SDL_CreateWindow(name.c_str(), width, height, 0);
        if (_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        _renderer = SDL_CreateRenderer(_window, NULL);
        if (_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(_window);
            SDL_Quit();
            return false;
        }
        return true;
    }

    void Renderer::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    }

    void Renderer::SetColourf(float r, float g, float b, float a)
    {
		SDL_SetRenderDrawColorFloat(_renderer, r, g, b, a);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2)
    {
        SDL_RenderLine(_renderer, x1, y1, x2, y2);
    }

    void Renderer::DrawPoint(float x, float y)
    {
        SDL_RenderPoint(_renderer, x, y);
    }

    void Renderer::DrawTexture(Texture* texture, float x, float y)
    {
		vec2 size = texture->GetSize();

		SDL_FRect destRect;
        destRect.x = x;
		destRect.y = y;
        destRect.w = size.x;
		destRect.h = size.y;

		SDL_RenderTexture(_renderer, texture->_texture, NULL, &destRect);
    }

    void Renderer::Clear()
    {
        SDL_RenderClear(_renderer);
    }

    void Renderer::Present()
    {
        SDL_RenderPresent(_renderer);
    }
}