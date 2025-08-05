#pragma once
#include "Math/Vector2.h"
#include <vector>
#include <array>
#include <string>
#include <SDL3/SDL.h>


namespace whermst {
	class InputSystem {
	public:
		enum class MouseButton : uint8_t {
			Left,
			Middle,
			Right
		};
	public:
		InputSystem() = default;

		bool Initialize();
		void Close();

		void Update();


		//KEYBOARD INPUT
		bool GetKeyDown(uint8_t key) const { return _keyboardState[key]; }
		bool GetPreviousKeyDown(uint8_t key) const { return _prevKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return _keyboardState[key] && !_prevKeyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return !_keyboardState[key] && _prevKeyboardState[key]; }

		//MOUSE INPUT
		bool GetMouseButtonDown(MouseButton button) const {   return _mouseButtonState[(uint8_t)button]; }
		bool GetPreviousMouseButtonDown(MouseButton button) const {  return _prevMouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonPressed(MouseButton button) const {  return _mouseButtonState[(uint8_t)button] && !_prevMouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonReleased(MouseButton button) const {  return !_mouseButtonState[(uint8_t)button] && _prevMouseButtonState[(uint8_t)button]; }

		const vec2& GetMousePosition() const { return _mousePosition; }
		const vec2& GetPreviousMousePosition() const { return _prevMousePosition; }

		void StartTextInput(class Renderer& renderer);
		void StopTextInput(class Renderer& renderer);
		void HandleEvent(const SDL_Event& e);

		std::string GetTextInput() const;
		void ClearTextInput();

	private:
		std::vector<bool> _keyboardState;
		std::vector<bool> _prevKeyboardState;

		vec2 _mousePosition{ 0, 0 };
		vec2 _prevMousePosition{ 0, 0 };

		std::array<bool, 3> _mouseButtonState{ false, false, false };
		std::array<bool, 3> _prevMouseButtonState{ false, false, false };

		std::string _textBuffer;
	};
}