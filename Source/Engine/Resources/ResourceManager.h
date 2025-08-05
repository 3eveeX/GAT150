#pragma once	 
#include "Core/StringHelper.h"
#include "Resource.h"
#include <string>
#include <map>
#include <iostream>

namespace whermst{
	class ResourceManager {
	public:
		template <typename T, typename... TArgs>
		res_t<T> Get(const std::string& name, TArgs&& ... args);

		static ResourceManager& Instance()
		{
			static ResourceManager instance;
			return instance;
		}


	private:
		std::map<std::string, res_t<Resource>> _resources;
	private:
		ResourceManager() = default;
	};

	template <typename T, typename... TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& name, TArgs&& ... args)
	{
		std::string key = tolower(name);

		auto iter = _resources.find(key);
		if (iter != _resources.end())
		{
			auto base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>(base); 
			if (resource == nullptr)
			{
				std::cerr << "Resource type mismatch: " << key << " is not of type " << typeid(T).name() << std::endl;
				return res_t<T>();
			}
			return resource;
		}

		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(key, std::forward<TArgs>(args)...) == false) {
			std::cerr << "Failed to load resource: " << key << std::endl;
			return res_t<T>();
		}

		_resources[key] = resource;

		return resource;
	}

	
}
