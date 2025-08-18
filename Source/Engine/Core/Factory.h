#pragma once
#include "Framework/Object.h"
#include "Singleton.h"
#include "StringHelper.h"
#include "Logger.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname { \
public: \
    Register##classname() { \
        whermst::Factory::Instance().Register<classname>(#classname); \
    } \
}; \
Register##classname registered_instance;

namespace whermst {
	class CreatorBase {
	public:
		~CreatorBase() = default;
		virtual std::unique_ptr<Object> Create() = 0;

	};

	template<typename T>
		requires std::derived_from<T, Object>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<Object> Create() override {
			return std::make_unique<T>();
		}
	};

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
			requires std::derived_from<T, Object>
		void Register(const std::string& typeName);

		template<typename T = Object>
			requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& typeName);
	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> _registry;
	};

	template<typename T>
		requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& typeName)
	{
		std::string key = tolower(typeName);
		_registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
		requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& typeName)
	{
		std::string key = tolower(typeName);
		auto it = _registry.find(key);
		if (it != _registry.end()) {
			return it->second->Create();
		}

		Logger::Error("Factory: Type '{}' is not registered.", typeName);

		return nullptr;
		
	}
}