#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"

class SpaceGame : public whermst::Game {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver
	};
public:

	SpaceGame() = default;

	// Inherited via Game
	bool Initialize() override;

	void Update(float dt) override;

	void Shutdown() override;

	void Draw(class whermst::Renderer& renderer) override;

	void OnPlayerDeath();

private:
	GameState _gameState = GameState::Initialize;
	float _enemySpawnTimer{ 0 };
	float _stateTimer{ 0 };
	float _bgmTimer{ 0 };
	std::string _playerName = "";

	std::unique_ptr<whermst::Text> _titleText;
	std::unique_ptr<whermst::Text> _scoreText;
	std::unique_ptr<whermst::Text> _livesText;
	std::unique_ptr<whermst::Text> _scoreboardText;
	std::unique_ptr<whermst::Text> _nameText;
};

