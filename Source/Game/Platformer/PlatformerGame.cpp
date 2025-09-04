 #include "PlatformerGame.h"
#include "Engine.h"
#include "EngineMinimal.h"

bool PlatformerGame::Initialize() {
	OBSERVER_ADD("PlayerDeath");
	OBSERVER_ADD(AddPoints);

	_scene = std::make_unique<whermst::Scene>(this);
	_scene->Load("scenes/Level.json");
	_scene->Load("scenes/Prototypes.json");

	_scoreText = std::make_unique<whermst::Text>(whermst::Resources().GetWithID<whermst::Font>("uifont", "../8bitOperatorPlus8-Regular.ttf", 48.0f));
	_titleText = std::make_unique<whermst::Text>(whermst::Resources().GetWithID<whermst::Font>("winfont", "../8bitOperatorPlus8-Regular.ttf", 200.0f));
	return true;
}

void PlatformerGame::Update(float dt) {
	switch (_gameState)
	{
	case PlatformerGame::GameState::Initialize:
		_gameState = PlatformerGame::GameState::Title;
		break;
	case PlatformerGame::GameState::Title:

		if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
			_gameState = GameState::StartGame;
		}

		break;
	case PlatformerGame::GameState::StartGame:
		_enemySpawnTimer = 0;
		_gameState = GameState::StartRound;
		break;
	case PlatformerGame::GameState::StartRound:
		SpawnPlayer();
		_gameState = GameState::Game;
		break;
	case PlatformerGame::GameState::Game:
	{
		_enemySpawnTimer += dt;
		if (_enemySpawnTimer >= 20.0f) {
			_enemySpawnTimer = 0;
			SpawnCrate();
		}
		auto crate = _scene->GetActorByName("crate");
		auto player = _scene->GetActorByName("PlatformPlayer");
		if (crate && (crate->transform.position.y > whermst::GetEngine().GetRenderer().GetHeight() || (crate->transform.position.x < 0) || crate->transform.position.x > whermst::GetEngine().GetRenderer().GetWidth())) {
			crate->destroyed = true;
			_score += 1;
		}
		if (player->transform.position.y > whermst::GetEngine().GetRenderer().GetHeight()) {
			player->destroyed = true;
			_gameState = GameState::PlayerDead;
		}
		if (_score == 10) {
			_gameState = GameState::PlayerDead;
		}
	}
	break;
	case PlatformerGame::GameState::PlayerDead:
		_score = 0;
		_stateTimer += dt;
		if (_stateTimer >= 3.0f) {
			_gameState = GameState::GameOver;
		}
		break;
	case PlatformerGame::GameState::GameOver:
		if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_RETURN)) {
			_stateTimer = 0;
			_gameState = GameState::Title;
		}
		break;
	default:
		break;
	}

	_scene->Update(whermst::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Shutdown() {
}

void PlatformerGame::Draw(class whermst::Renderer& renderer) {

	_scene->Draw(renderer);
	whermst::GetEngine().GetPT().Draw(renderer);

	if (_gameState == GameState::Game) {
		_scoreText->Create(renderer, "Score: " + std::to_string(_score), whermst::vec3{ 1, 1, 1 });
		_scoreText->Draw(renderer, 20, 20);
	}
	if (!(_gameState == GameState::Game || _gameState == GameState::Title || _gameState == GameState::Initialize)){
		if (_scene->GetActorByName("PlatformPlayer")) {
			_titleText->Create(renderer, "You Win", whermst::vec3{ 1, 1, 1 });
		}
		else {
			_titleText->Create(renderer, "You Lose", whermst::vec3{ 1, 1, 1 });
		}
		_titleText->Draw(renderer, 300, 400);
	}
	if (_gameState == GameState::Title) {
		_titleText->Create(renderer, "Platformer Game", whermst::vec3{ 1, 1, 1 });
		_titleText->Draw(renderer, 150, 20);
		_scoreText->Create(renderer, "press [[SPACE]] to start", whermst::vec3{ 1, 1, 1 });
		_scoreText->Draw(renderer, 200, 330);
	}
	if (_gameState == GameState::GameOver) {
		_scoreText->Create(renderer, "press [[ENTER]] to go back to title screen", whermst::vec3{ 1, 1, 1 });
		_scoreText->Draw(renderer, 300, 600);
	}
}

void PlatformerGame::OnPlayerDeath() {
	_gameState = GameState::PlayerDead;
	_stateTimer = 0;
}

void PlatformerGame::OnNotify(const whermst::Event& event) {
}



void PlatformerGame::SpawnPlayer() {
	auto player = whermst::Instantiate<whermst::Actor>("PlatformPlayer");
	player->transform.position = whermst::vec2{ 500, 100 };
	_scene->AddActor(std::move(player), true);
}
void PlatformerGame::SpawnCrate() {
	auto crate = whermst::Instantiate<whermst::Actor>("crate");
	crate->transform.position = whermst::vec2{ 500, 100 } + whermst::vec2{ whermst::random::getReal(50.0f, 600.0f), 0 };
	_scene->AddActor(std::move(crate), true);
}