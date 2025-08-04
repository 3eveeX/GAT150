#include "Texture.h"  
#include "Renderer.h"  
#include <SDL3/SDL.h>  
#include <SDL3_image/SDL_image.h>  

namespace whermst  
{  
    Texture::~Texture()  
    {  
        // if texture exists, destroy texture  
        if (_texture != nullptr) SDL_DestroyTexture(_texture);  
    }  

    bool Texture::Load(const std::string& fileName, Renderer& renderer)  
    {  
        // load image onto surface  
        SDL_Surface* surface = IMG_Load(fileName.c_str());  
        if (surface == nullptr)  
        {  
            std::cerr << "Could not load image: " << fileName << std::endl;  
            return false;  
        }  

        // create texture from surface, texture is a friend class of renderer  
        _texture = static_cast<SDL_Texture*>(SDL_CreateTextureFromSurface(renderer._renderer, surface));  
        // once texture is created, surface can be freed up  
        SDL_DestroySurface(surface);  
        if (_texture == nullptr)  
        {  
            std::cerr << "Could not create texture: " << fileName << std::endl;  
            return false;  
        }  

        return true;  
    }  

    vec2 Texture::GetSize()  
    {  
        float width, height;  
        SDL_GetTextureSize(static_cast<SDL_Texture*>(_texture), &width, &height);  
        return vec2(width, height);  
    }  
}
