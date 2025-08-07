#pragma once
#include <memory>
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Resources/ResourceManager.h"

namespace whermst
{
	class ParticleSystem;

	class Engine : public Singleton<Engine>{
		public:
		
		
		bool Initialize();
		void Update();
		void Shutdown();
		//void Draw();

		Renderer& GetRenderer(){ return *_renderer;}
		InputSystem& GetInput(){ return *_input;}
		AudioSystem& GetAudio(){ return *_audio;}
		ParticleSystem& GetPT() { return *_particle; }

		Time& GetTime(){return _time;}

	
	private:
		friend class Singleton<Engine>;
		Engine() = default;
	private:
		Time _time;

		std::unique_ptr<class Renderer> _renderer;
		std::unique_ptr<class InputSystem> _input;
		std::unique_ptr<class AudioSystem> _audio;
		std::unique_ptr<class ParticleSystem> _particle;
	};
	inline Engine& GetEngine() { return Engine::Instance(); }
}
