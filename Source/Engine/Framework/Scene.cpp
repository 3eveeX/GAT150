#include "Scene.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
#include "../Renderer/Renderer.h"


namespace whermst {
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		for (auto& actor : _actors) {
			actor->Update(dt);
		}
		// Remove destroyed actors from the scene
		for (auto iter = _actors.begin(); iter != _actors.end();) {
			if ((*iter)->destroyed) {
				iter = _actors.erase(iter);
			}			   
			else {
				iter++;
			}
		}

		//check for collisions
		for (auto& actorA : _actors) {
			for (auto& actorB : _actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				float distance = (actorA->transform.position - actorB->transform.position).Length();
				if (distance <= (actorA->GetRadius() + actorB->GetRadius())) {
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
	void Scene::AddActor(std::unique_ptr<class Actor> actor){

		actor->_scene = this; 
		_actors.push_back(std::move(actor));
	}
	
}