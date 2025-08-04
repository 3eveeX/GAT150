#include "SpaceGame.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Core/Random.h"
#include "../Engine/Engine.h"
#include "Renderer/Renderer.h"
#include "Enemy.h"
#include "GameData.h"
#include "Renderer/Font.h"
#include "Core/File.h"
#include "Renderer/ParticleSystem.h"



bool SpaceGame::Initialize()
{
   
	_scene = std::make_unique<whermst::Scene>(this);
	std::cout << whermst::file::GetCurrentDirectory() << std::endl;
	whermst::file::SetCurrentDirectory("Assets");
	std::cout << whermst::file::GetCurrentDirectory() << std::endl;
	whermst::GetEngine().GetAudio().PlaySound("bgm");
	_bgmTimer = 190;
    return true;

}    

void SpaceGame::Update(float dt)
{
    _bgmTimer -= dt;
    if (_bgmTimer <= 0) {
        whermst::GetEngine().GetAudio().PlaySound("bgm");
        _bgmTimer = 190;
	}
    switch (_gameState)
    {
    case SpaceGame::GameState::Initialize:
        _titleFont = std::make_shared<whermst::Font>();
		_titleFont->Load("8bitOperatorPlus8-Regular.ttf", 128);

        _uiFont = std::make_shared<whermst::Font>();
		_uiFont->Load("8bitOperatorPlus8-Regular.ttf", 128);

        _titleText = std::make_unique<whermst::Text>(_titleFont);
        _scoreText = std::make_unique<whermst::Text>(_uiFont);
        _livesText = std::make_unique<whermst::Text>(_uiFont);
        _scoreboardText = std::make_unique<whermst::Text>(_uiFont);
        _nameText = std::make_unique<whermst::Text>(_uiFont);
        
		_gameState = SpaceGame::GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        _scene->RemoveAllActors();
        if (whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            _gameState = SpaceGame::GameState::StartGame;
        }
        break;
        case SpaceGame::GameState::StartGame:
			ResetPoints();
			SetLives(3);
			_gameState = SpaceGame::GameState::StartRound;
			break;
    case SpaceGame::GameState::StartRound:
    {
        _scene->RemoveAllActors();
        std::shared_ptr<whermst::Model> model = std::make_shared<whermst::Model>(GameData::shipPoints, whermst::vec3{ 1.0f, 1.0f, 1.0f });
        whermst::Transform transform{ whermst::vec2{whermst::GetEngine().GetRenderer().GetWidth() * 0.5f, whermst::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 5 };
        auto player = std::make_unique<Player>(transform, model);
        player->speed = 500.0f;
        player->rotateRate = 180.0f;
        player->damping = .9f;
        player->fireTime = 0.5f;
		player->fireTimer = player->fireTime;
        player->name = "Player";
        player->tag = "Player";
        _scene->AddActor(std::move(player));
    }
	_gameState = SpaceGame::GameState::Game;
        break;
	case SpaceGame::GameState::Game:
        
        _enemySpawnTimer -= dt;
        if (_enemySpawnTimer <= 0) {
            _enemySpawnTimer = 4.0f;
			Player* player = _scene->GetActorByName<Player>("Player");
            if (player) {

                whermst::vec2 position = player->transform.position + whermst::random::onUnitCircle() * whermst::random::getReal(200.0f, 500.0f);

                std::shared_ptr<whermst::Model> enemyModel = std::make_shared<whermst::Model>(GameData::enemyPoints);
                whermst::Transform transform{ position, whermst::random::getReal(0.0f, 360.0f), 5 };
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
                enemy->hitPoints = whermst::random::getInt(1, 3); // Random hit points between 1 and 3
                if (enemy->hitPoints == 3) { 
                    enemyModel->SetColour(whermst::vec3{ 0.4f, 0.5f, 0.0f }); 
                    enemy->fireTime = 1.0f;
                    enemy->speed = 1.0f  + whermst::random::getReal(1.0f, 2.0f) * 100.0f;
                }
                else if (enemy->hitPoints == 2) { 
                    enemyModel->SetColour(whermst::vec3{ 0.7f, 0.6f, 0.1f }); 
                    enemy->fireTime = 2.0f;
                    enemy->speed = 1.0f  + whermst::random::getReal(1.0f, 2.0f) * 50.0f;
                }
                else if (enemy->hitPoints == 1) { 
                    enemyModel->SetColour(whermst::vec3{ 0.7f, 0.0f, 0.0f }); 
				    enemy->fireTime = 4.0f;
                    enemy->speed = 1.0f  + whermst::random::getReal(1.0f, 2.0f) * 10.0f;
                }
                  enemy->damping = 0.9f;
                  enemy->tag = "Enemy";
                  _scene->AddActor(std::move(enemy));
            }
        }

        break;
	case SpaceGame::GameState::PlayerDead:
        _stateTimer -= dt;
        if (_stateTimer <= 0) {
            _lives--;
            if (_lives <= 0) {
				_stateTimer = 3.0f;
		whermst::GetEngine().GetInput().StartTextInput(whermst::GetEngine().GetRenderer());
                _gameState = GameState::GameOver;
            }
            else {
                _gameState = GameState::StartRound;
            }
        }
		
		break;
    case SpaceGame::GameState::GameOver:
		_playerName = whermst::GetEngine().GetInput().GetTextInput();
        if (!_playerName.empty() && whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_RETURN)) {
			whermst::GetEngine().GetInput().StopTextInput(whermst::GetEngine().GetRenderer());
			std::string str = _playerName + ": " + std::to_string(_score) + "\n";
            std::string score = str.substr(str.find(": ") + 2);
			int highscore = std::stoi(score);
            std::cout << score << std::endl;
			if (whermst::file::Exists("Highscore.txt")) {
				whermst::file::WriteTextFile("Highscore.txt", str, true);
				whermst::file::SortFileByScore("Highscore.txt", ": ", 0, 3);
			}
			else {
				whermst::file::WriteTextFile("Highscore.txt", str);
			}
			_playerName = "";
			_gameState = GameState::Title;
        }
        else if (whermst::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_RETURN)) {
            whermst::GetEngine().GetInput().StopTextInput(whermst::GetEngine().GetRenderer());
			_playerName = "";
			_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }
    _scene -> Update(whermst::GetEngine().GetTime().GetDeltaTime());    
}

void SpaceGame::Shutdown()
{
    //
}

#include <fstream> // Ensure this include is present for std::ifstream and std::getline  

void SpaceGame::Draw(whermst::Renderer& renderer)  
{  
    if (_gameState == GameState::Title) {  
        _titleText->Create(renderer, "Unnamed Space Game", whermst::vec3{ 1, 1, 1 });  
        _titleText->Draw(renderer, 200, 20);  
        _titleText->Create(renderer, "[[SPACE]] to start", whermst::vec3{ 1, 1, 1 });  
        _titleText->Draw(renderer, 200, 330);  

		_titleText->Create(renderer, "Top 3 High Scores", whermst::vec3{ 1, 1, 1 });
		_titleText->Draw(renderer, renderer.GetWidth() / 5 - 200, renderer.GetHeight()/1.5f - 110, 1.5f);
        if (whermst::file::Exists("Highscore.txt")) {
            std::ifstream file("Highscore.txt");
            if (file.is_open()) { // Ensure the file is successfully opened
                std::string line;
                float y = renderer.GetHeight()/1.5f; // Starting Y position

                while (std::getline(file, line)) {
                    _scoreboardText->Create(renderer, line, whermst::vec3{ 1, 1, 1 });
                    
                    _scoreboardText->Draw(renderer, renderer.GetWidth()/2 - 300, y, 0.5f);
                    y += 110; // Move down for next line
                }
            } else {
                std::cerr << "Failed to open Highscore.txt" << std::endl;
            }
        }
    }
    if (_gameState == GameState::GameOver) {  
        _titleText->Create(renderer, "GameOver", whermst::vec3{ 1, 1, 1 });  
        _titleText->Draw(renderer, 300, 600);  
		_titleText->Create(renderer, "Enter your name:", whermst::vec3{ 1, 1, 1 });
		_titleText->Draw(renderer, 175, 700);
        if (!whermst::GetEngine().GetInput().GetTextInput().empty()) {
            _nameText->Create(renderer, whermst::GetEngine().GetInput().GetTextInput(), whermst::vec3{ 1, 1, 1 });  
            _nameText->Draw(renderer, 300, 400);  
        }  
    }  
    if (_gameState != GameState::Title) {
        _scoreText->Create(renderer, "Score: " + std::to_string(_score), whermst::vec3{1, 1, 1});
        _scoreText->Draw(renderer, 20, 20);

        _livesText->Create(renderer, "Lives: " + std::to_string(_lives), whermst::vec3{1, 1, 1});
        _livesText->Draw(renderer, renderer.GetWidth() - 700, 20);
    }
    whermst::GetEngine().GetPT().Draw(renderer);
    _scene -> Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
_gameState = GameState::PlayerDead;
_stateTimer = 2.0f;
}
