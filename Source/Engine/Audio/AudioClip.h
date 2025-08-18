#pragma once  
#include "Resources/Resource.h"  
#include "Core/Factory.h"   

namespace whermst {  

	
	class AudioClip : public Resource {  
	public:  
		AudioClip() = default;  
		~AudioClip();  

		bool Load(const std::string& fileName, class AudioSystem& audioSystem);  
	private:  
		friend class AudioSystem;  
		FMOD::Sound* _sound{nullptr};  
	};  
}
