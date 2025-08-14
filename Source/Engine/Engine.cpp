#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"

namespace whermst
{
	
	bool Engine::Initialize()
	{
		_renderer = std::make_unique<whermst::Renderer>();

		_renderer->Initialize();
		_renderer->CreateWindow("Unnamed Space Game", 1920, 1536, true);

		_input = std::make_unique<whermst::InputSystem>();
		_input->Initialize();

		_audio = std::make_unique<whermst::AudioSystem>();
		_audio->Initialize();

		_particle = std::make_unique<whermst::ParticleSystem>();
		_particle->Initialize(5000);

		return true;
	}
	void Engine::Update()
	{
		_time.Tick();
		_input->Update();
		_audio->Update();
		_particle->Update(_time.GetDeltaTime());
	}
	void Engine::Shutdown()
	{

		Resources().Clear();

	_particle->Shutdown();
	_audio->Close();
	_input->Close();
	_renderer->CloseWindow();

	}
}