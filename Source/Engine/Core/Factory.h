#pragma once
#include "Framework/Object.h"
#include "Singleton.h"
#include "StringHelper.h"
#include "Logger.h"
#include "Math/Transform.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname { \
public: \
    Register##classname() { \
        whermst::Factory::Instance().Register<classname>(#classname); \
		Logger::Info("{} registered", #classname); \
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

	template<typename T>
		requires std::derived_from<T, Object>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : _prototype(std::move(prototype)) {
			if (!_prototype) {
				Logger::Error("PrototypeCreator: Prototype cannot be null.");
			}
		}
		std::unique_ptr<Object> Create() override {
			return _prototype->Clone();
		}
	private:
		std::unique_ptr<T> _prototype;
	};



	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
			requires std::derived_from<T, Object>
		void Register(const std::string& typeName);
		
		template<typename T>
			requires std::derived_from<T, Object>
		void RegisterPrototype(const std::string& typeName, std::unique_ptr<T> prototype);

		template<typename T = Object>
			requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& typeName);

		void RemoveAll() { _registry.clear(); }
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
	inline void Factory::RegisterPrototype(const std::string& typeName, std::unique_ptr<T> prototype)
	{
		std::string key = tolower(typeName);
		_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
	}

	template<typename T>
		requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& typeName)
	{
		std::string key = tolower(typeName);
		auto it = _registry.find(key);
		if (it != _registry.end()) {
			auto object  =  it->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				object.release(); 
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Factory: Type '{}' is not of the expected type '{}'.", typeName, typeid(T).name());
		}
		else {
			Logger::Error("Factory: Type '{}' is not registered.", typeName);
		}

		return nullptr;
		
	}

	template<typename T>
		requires std::derived_from<T, Object>
	std::unique_ptr<T> Instantiate(const std::string& typeName) {
		auto instance = Factory::Instance().Create<T>(typeName);
		return instance;
	}
	template<typename T>
		requires std::derived_from<T, Object>
	std::unique_ptr<T> Instantiate(const std::string& typeName, const vec2& position, float rotation, float scale) {
		auto instance = Factory::Instance().Create<T>(typeName);
		if (instance) {
			instance->transform.position = position;
			instance->transform.rotation = rotation;
			instance->transform.scale = scale;
		}
		return instance;
	}

	template<typename T>
		requires std::derived_from<T, Object>
	std::unique_ptr<T> Instantiate(const std::string& typeName, const Transform& transform) {
		auto instance = Factory::Instance().Create<T>(typeName);
		if (instance) {
			instance->transform = transform;
		}
		return instance;
	}
}