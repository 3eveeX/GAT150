#pragma once
#include "Core/StringHelper.h"
#include "Core/Serializable.h"
#include <vector>
#include <memory>
#include <string>
#include <list>

namespace whermst {
	class Actor;
	class Game;
	class Scene : public ISerializable{
	public:
		Scene(Game* game) : _game{ game } {}

		bool Load(const std::string& sceneName);
		 void Read(const json::value_t& value) override;
		
		 void Update(float dt);
		
		 void Draw(class Renderer& renderer);
		 void AddActor(std::unique_ptr< Actor> actor, bool start);

		  template <typename T = Actor>
		  T* GetActorByName(const std::string& name);


		 template <typename T = Actor>
		 std::vector<T*> GetActorsByTag(const std::string& tag);

		 class Game* GetGame() const { return _game; }
		 void RemoveAllActors(bool force = false) {
			 for (auto iter = _actors.begin(); iter != _actors.end();) {
				 if (!((*iter)->persistent) || force) {
					 iter = _actors.erase(iter);
				 }
				 else {
					 iter++;
				 }
			 }
		 }
		

	private:
		class Game* _game{ nullptr };
		std::list<std::unique_ptr<Actor>> _actors;

	
	};
	/// <summary>
	/// Finds and returns a pointer to an actor in the scene by name, cast to the specified type.
	/// </summary>
	/// <typeparam name="T">The type to which the found actor should be cast.</typeparam>
	/// <param name="name">The name of the actor to search for (case-insensitive).</param>
	/// <returns>A pointer to the actor of type T with the specified name, or nullptr if not found.</returns>
	template <typename T>
	 inline T* Scene::GetActorByName(const std::string& name)
	 {
		 for (auto& actor : _actors) {
			 if (whermst::tolower(actor->name) == whermst::tolower(name)) {
				 return dynamic_cast<T*>(actor.get());
			 }
		 }
		 return nullptr;
	 }

	 /// <summary>
	 /// Retrieves all actors with a matching tag and casts them to the specified type.
	 /// </summary>
	 /// <typeparam name="T">The type to which matching actors will be cast.</typeparam>
	 /// <param name="tag">The tag to search for among the actors.</param>
	 /// <returns>A vector of pointers to actors of type T that have the specified tag.</returns>
	 template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actor : _actors) {
			if (whermst::tolower(actor->tag) == whermst::tolower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}
		return results;
	}
}