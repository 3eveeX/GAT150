#include "AudioSystem.h"
#include "AudioClip.h"

namespace whermst {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="result"></param>
	/// <returns></returns>
	bool AudioSystem::CheckFmodResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			Logger::Error("{}", FMOD_ErrorString(result));
			return false;
		}

		return true;
	}

	bool AudioSystem::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&_system);
		if (!CheckFmodResult(result)) return false;

		void* extradriverdata = nullptr;
		if (!CheckFmodResult(result)) return false;
		_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		return true;
	}
	void AudioSystem::Close() {
		CheckFmodResult(_system->release());
	}

	void AudioSystem::Update() {
		CheckFmodResult(_system->update());
	}


	bool AudioSystem::Load(const std::string& filename, const std::string& name)
	{
		std::string key = (name.empty()) ? filename : name;

		//check if key exists in sounds
		if (_sounds.find(key) != _sounds.end()) {
			Logger::Error("Audio system {} already exists", key);
			return false;
		}

		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = _system->createSound( filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFmodResult(result)) return false;
		
		//insert sounds into map
		_sounds[key] = sound;

		return true;
	}
	bool AudioSystem::PlaySound(const std::string& name/*, const int volume*/)
	{
		std::string key = name;
		//convert to lowercase
		key = tolower(key);

		//check if sound exists in sounds map

		if (_sounds.find(name) == _sounds.end()) {
			Logger::Error("Audio system {} doesn't exist", key);
			return false;
		}

		FMOD_RESULT result = _system -> playSound(_sounds[name], 0, false, nullptr);
		if (!CheckFmodResult(result)) return false;
		/*FMOD_RESULT volumeResult = _system->setVolume((float)volume / 100.0f);
		if (!CheckFmodResult(volumeResult)) return false;*/
		return true;
	}
	bool AudioSystem::PlaySound(AudioClip& audioClip)
	{
		FMOD_RESULT result = _system->playSound(audioClip._sound, 0, false, nullptr);
		if (!CheckFmodResult(result)) return false;
		return true;
	}
}
