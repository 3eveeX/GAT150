#include "EnginePCH.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/TextureAnimation.h"
#include "Engine.h"

namespace whermst {
	FACTORY_REGISTER(Animator)

	void Animator::Start()
	{
		_spriteRenderer = owner->GetComponent<SpriteRenderer>();
		if (!_spriteRenderer) {
			Logger::Warning("Animator component requires a SpriteRenderer component on the same actor");
			return;
		}
		//load all animations
		for (auto& animation : _animations) {
			animation.second.textureAnimation = Resources().Get<TextureAnimation>(animation.second.textureAnimationName, GetEngine().GetRenderer());
			if (!animation.second.textureAnimation) {
				Logger::Warning("Could not load TextureAnimation {} in Animator component", animation.second.textureAnimationName);
			}
			else {
				Logger::Info("Animator animation {}, texture {} loaded", animation.first, animation.second.textureAnimationName);
			}
		}
		auto it = _animations.begin();
		std::string name = it->first;
		Play(name);
	}

	void Animator::Update(float dt)
	{
		if (_paused || !_currentAnimation.textureAnimation) return;

		_frameTimer -= dt * speedMultiplier;
		if(_frameTimer <= 0) {
			_frameTimer = 1.0f / _currentAnimation.textureAnimation->GetFPS();
			frame++;
			if (frame >= _currentAnimation.textureAnimation->GetTotalFrames()) {
				if (_currentAnimation.textureAnimation->IsLooping()) {
					frame = 0;
				}
				else {
					frame = _currentAnimation.textureAnimation->GetTotalFrames() - 1;
				}
			}
			
			//update sprite renderer
			if (_spriteRenderer) {
				_spriteRenderer->textureRect = _currentAnimation.textureAnimation->GetFrameRect(frame);
			}
		}
	}

	void Animator::Play(const std::string& textureAnimationName, bool resetFrame)
	{
		if (equalsIgnoreCase(textureAnimationName, _currentAnimationName)) return;

		auto it = _animations.find(tolower(textureAnimationName));
		if (it == _animations.end()) {
			Logger::Warning("Could not find animation {} in Animator component", textureAnimationName);
			return;
		}

		_currentAnimationName = textureAnimationName;
		_currentAnimation = it->second;

		if (resetFrame) frame = 0;
		_frameTimer = 1.0f / _currentAnimation.textureAnimation->GetFPS();

		if (_spriteRenderer) {
			_spriteRenderer->_texture = _currentAnimation.textureAnimation->GetTexture();
			_spriteRenderer->textureRect = _currentAnimation.textureAnimation->GetFrameRect(frame);
		}

	}

	void Animator::Read(const json::value_t& value)
	{
		Object::Read(value);
		JSON_READ(value, frame);
		
		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray()) {
			for (auto& animatorValue : JSON_GET(value, animations).GetArray()) {
				std::string name;
				std::string textureAnimationName;

				JSON_READ(animatorValue, name);

				JSON_READ_NAME(animatorValue, "textureAnimation", textureAnimationName);

				TextureAnimInfo textureAnimInfo;
				textureAnimInfo.textureAnimationName = textureAnimationName;
				_animations[tolower(name)] = textureAnimInfo;
			}
		}
		
	}
}