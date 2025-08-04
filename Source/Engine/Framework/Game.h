#pragma once
#include <memory>

namespace whermst
{
	class Game {
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Shutdown() = 0;
		virtual void Draw(class Renderer& renderer) = 0;

		void AddPoints(int points) {
			_score += points;
		}
		int GetPoints() const {
			return _score;
		}
		void ResetPoints() {
			_score = 0;
		}

		void SetLives(int lives) {
			_lives = lives;
		}

		int GetLives() const {
			return _lives;
		}

	protected:
		std::unique_ptr<class Scene> _scene;
		int _score{ 0 };
		int _lives{ 3 };
	};
}
