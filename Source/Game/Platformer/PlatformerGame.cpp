 #include "PlatformerGame.h"
#include "Engine.h"
#include "EngineMinimal.h"

bool PlatformerGame::Initialize() {
	OBSERVER_ADD("PlayerDeath");
	OBSERVER_ADD(AddPoints);

	_scene = std::make_unique<whermst::Scene>(this);
	_scene->Load("scenes/Level.json");
	_scene->Load("scenes/Prototypes.json");

	return true;
}

void PlatformerGame::Update(float dt) {
	switch (_gameState)
	{
	case PlatformerGame::GameState::Initialize:
		_gameState = PlatformerGame::GameState::StartRound;
		break;
	case PlatformerGame::GameState::Title:
		break;
	case PlatformerGame::GameState::StartGame:
		break;
	case PlatformerGame::GameState::StartRound:
		SpawnPlayer();
		_gameState = GameState::Game;
		break;
	case PlatformerGame::GameState::Game:
		break;
	case PlatformerGame::GameState::PlayerDead:
		break;
	case PlatformerGame::GameState::GameOver:
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
}

void PlatformerGame::OnPlayerDeath() {
}

void PlatformerGame::OnNotify(const whermst::Event& event) {
}



void PlatformerGame::SpawnPlayer() {
	auto player = whermst::Instantiate<whermst::Actor>("PlatformPlayer");
	player->transform.position = whermst::vec2{ 500, 100 } + whermst::random::getReal(100.0f, 300.0f);
	_scene->AddActor(std::move(player), true);
}
void PlatformerGame::SpawnEnemy() {
	auto enemy = whermst::Instantiate<whermst::Actor>("PlatformEnemy");
	enemy->transform.position = whermst::vec2{ 500, 100 } + whermst::random::getReal(100.0f, 300.0f);
	_scene->AddActor(std::move(enemy), true);
}