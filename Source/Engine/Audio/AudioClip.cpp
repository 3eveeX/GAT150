#include "EnginePCH.h"
#include "AudioClip.h"
#include "AudioSystem.h"

namespace whermst {
    AudioClip::~AudioClip()
    {
        //if (_sound) _sound->release();
    }

    bool AudioClip::Load(const std::string& fileName, AudioSystem& audioSystem)
    {
        FMOD_RESULT result = audioSystem._system->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &_sound);
        if(!AudioSystem::CheckFmodResult(result)) return false;

        return true;
    }
}
