#include "InputSystem.h"
#include <SDL3/SDL.h>
#include "Renderer/Renderer.h"  
namespace whermst {
	bool InputSystem::Initialize() {
		int numKeys;
		const bool* keyboardState = SDL_GetKeyboardState(&numKeys);

		_keyboardState.resize(numKeys);
		std::copy(keyboardState, keyboardState + numKeys, _keyboardState.begin());
		_prevKeyboardState = _keyboardState;

		SDL_GetMouseState(&_mousePosition[0], &_mousePosition[1]);
		_prevMousePosition = _mousePosition;

		return true;
	}
	void InputSystem::Close() {
		//	
	}
	void InputSystem::Update() {
		//keyboard input
		_prevKeyboardState = _keyboardState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + _keyboardState.size(), _keyboardState.begin());

		//mouse input
		_prevMousePosition = _mousePosition;

		_prevMouseButtonState = _mouseButtonState;
		uint32_t mouseButtonState = SDL_GetMouseState(&_mousePosition[0], &_mousePosition[1]);
		_mouseButtonState[(uint8_t)MouseButton::Left] = mouseButtonState & SDL_BUTTON_LMASK;
		_mouseButtonState[(uint8_t)MouseButton::Middle] = mouseButtonState & SDL_BUTTON_MMASK;
		_mouseButtonState[(uint8_t)MouseButton::Right] = mouseButtonState & SDL_BUTTON_RMASK;

	}
	void InputSystem::StartTextInput(class Renderer& renderer)
	{
		SDL_StartTextInput(renderer.GetWindow());
		_textBuffer.clear();
		_textBuffer = "";
	}

	void InputSystem::StopTextInput(class Renderer& renderer)
	{
		SDL_StopTextInput(renderer.GetWindow());
	}

    void InputSystem::HandleEvent(const SDL_Event& e)  
    {  
        if (e.type == SDL_EVENT_TEXT_INPUT) {  
            // Append new typed characters to the buffer  
            _textBuffer += e.text.text;  
        }  
        else if (e.type == SDL_EVENT_KEY_DOWN) {  
            if (e.key.key == SDLK_BACKSPACE && !_textBuffer.empty()) {  
                _textBuffer.pop_back();  
            }  
        }  
    }

	std::string InputSystem::GetTextInput() const
	{
		return _textBuffer;
	}

	void InputSystem::ClearTextInput()
	{
		_textBuffer.clear();
		
	}
	
}