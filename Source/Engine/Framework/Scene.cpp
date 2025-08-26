#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Components/Collider.h"


namespace whermst {
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		for (auto& actor : _actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}
		// Remove destroyed actors from the scene
		std::erase_if(_actors, [](auto& actor) { return actor->destroyed; });
		/*for (auto iter = _actors.begin(); iter != _actors.end();) {
			if ((*iter)->destroyed) {
				iter = _actors.erase(iter);
			}			   
			else {
				iter++;
			}
		}*/

		//check for collisions
		for (auto& actorA : _actors) {
			for (auto& actorB : _actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA|| !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
	
	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : _actors) {
			actor->Draw(renderer);
		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership of the actor to the scene.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added. Ownership of the actor is transferred to the scene.</param>
	void Scene::AddActor(std::unique_ptr<class Actor> actor, bool start){

		actor->_scene = this;
		if (start) actor->Start();
		_actors.push_back(std::move(actor));
	}

	bool Scene::Load(const std::string& sceneName)
	{
		whermst::json::document_t document;
		if (!whermst::json::Load(sceneName, document)) {
			Logger::Error("Scene: Failed to load scene file '{}'.", sceneName);
			return false;
		}
		Read(document);

		for (auto& actor : _actors) {
			actor->Start();
		}

		return true;
	}

	void Scene::Read(const json::value_t& value)
	{
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);
				AddActor(std::move(actor), false);
			}
		}
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create("Actor");
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype(name, std::move(actor));
			}
		}
	}
	
}