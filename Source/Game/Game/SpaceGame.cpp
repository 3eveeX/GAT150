#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "../GamePCH.h"



bool SpaceGame::Initialize()
{
   
	_scene = std::make_unique<whermst::Scene>(this);
	std::cout << whermst::file::GetCurrentDirectory() << std::endl;
	whermst::file::SetCurrentDirectory("Assets");
	std::cout << whermst::file::GetCurrentDirectory() << std::endl;
    _titleText = std::make_unique<whermst::Text>(whermst::Resources().GetWithID<whermst::Font>("titlefont", "8bitOperatorPlus8-Regular.ttf", 128.0f));
    _scoreText = std::make_unique<whermst::Text>(whermst::Resources().GetWithID<whermst::Font>("uifont", "8bitOperatorPlus8-Regular.ttf", 48.0f));
    _livesText = std::make_unique<whermst::Text>(whermst::Resources().GetWithID<whermst::Font>("uifont", "8bitOperatorPlus8-Regular.ttf", 48.0f));
    _scoreboardText = std::make_unique<whermst::Text>(whermst::Resources().GetWithID<whermst::Font>("uifont", "8bitOperatorPlus8-Regular.ttf", 48.0f));
    _nameText = std::make_unique<whermst::Text>(whermst::Resources().GetWithID<whermst::Font>("titlefont", "8bitOperatorPlus8-Regular.ttf", 128.0f));
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
        whermst::Transform transform{ whermst::vec2{whermst::GetEngine().GetRenderer().GetWidth() * 0.5f, whermst::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 1 };
        auto player = std::make_unique<Player>(transform); // , whermst::Resources().Get<whermst::Texture>("player.png", whermst::GetEngine().GetRenderer()));
        player->speed = 500.0f;
        player->rotateRate = 180.0f;
        
        player->fireTime = 0.5f;
		player->fireTimer = player->fireTime;
        player->name = "Player";
        player->tag = "Player";
        auto spriteRenderer = std::make_unique<whermst::SpriteRenderer>();
        spriteRenderer->textureName = "player.png";
		player->_texture = whermst::Resources().Get<whermst::Texture>("player.png", whermst::GetEngine().GetRenderer());
		auto rb = std::make_unique<whermst::Rigidbody>();

        auto collider = std::make_unique<whermst::CircleCollider2d>();
        collider->radius = 40;
        player->AddComponent(std::move(collider));

		rb->damping = 0.9f;
		player->AddComponent(std::move(rb));
        player->AddComponent(std::move(spriteRenderer));
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
                whermst::Transform transform{ position, whermst::random::getReal(0.0f, 360.0f), 1.0f };
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform);// , whermst::Resources().Get<whermst::Texture>("player.png", whermst::GetEngine().GetRenderer()));
                auto spriteRenderer = std::make_unique<whermst::SpriteRenderer>();
                enemy->hitPoints = whermst::random::getInt(1, 3); // Random hit points between 1 and 3
                if (enemy->hitPoints == 3) { 
                    spriteRenderer->textureName = "enemy-3life.png";
                    //enemy->_texture = whermst::Resources().Get<whermst::Texture>("enemy-3life.png", whermst::GetEngine().GetRenderer());
                    enemy->fireTime = 1.0f;
                    enemy->speed = 1.0f  + whermst::random::getReal(1.0f, 2.0f) * 100.0f;
                }
                else if (enemy->hitPoints == 2) { 
                    spriteRenderer->textureName = "enemy-2life.png";
                    //enemy->_texture = whermst::Resources().Get<whermst::Texture>("enemy-2life.png", whermst::GetEngine().GetRenderer());
                    enemy->fireTime = 2.0f;
                    enemy->speed = 1.0f  + whermst::random::getReal(1.0f, 2.0f) * 50.0f;
                }
                else if (enemy->hitPoints == 1) { 
                    spriteRenderer->textureName = "enemy-1life.png";
                    //enemy->_texture = whermst::Resources().Get<whermst::Texture>("enemy-1life.png", whermst::GetEngine().GetRenderer());
				    enemy->fireTime = 4.0f;
                    enemy->speed = 1.0f  + whermst::random::getReal(1.0f, 2.0f) * 10.0f;
                }
                auto rb = std::make_unique<whermst::Rigidbody>();
                rb->damping = 0.9f;
                enemy->AddComponent(std::move(rb));
                  enemy->tag = "Enemy";
                  auto collider = std::make_unique<whermst::CircleCollider2d>();
                  collider->radius = 40;
                  enemy->AddComponent(std::move(collider));

                  enemy->AddComponent(std::move(spriteRenderer));
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

		_scoreText->Create(renderer, "Top 3 High Scores", whermst::vec3{ 1, 1, 1 });
		_scoreText->Draw(renderer, renderer.GetWidth() / 5.0f - 200, renderer.GetHeight()/1.5f - 110, 1.5f);
        if (whermst::file::Exists("Highscore.txt")) {
            std::ifstream file("Highscore.txt");
            if (file.is_open()) { // Ensure the file is successfully opened
                std::string line;
                float y = renderer.GetHeight()/1.5f; // Starting Y position

                while (std::getline(file, line)) {
                    _scoreboardText->Create(renderer, line, whermst::vec3{ 1, 1, 1 });
                    
                    _scoreboardText->Draw(renderer, renderer.GetWidth()/2.0f - 300, y, 0.5f);
                    y += 110; // Move down for next line
                }
            } else {
                Logger::Error("Could not retrieve scoreboard.");
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
        _livesText->Draw(renderer, renderer.GetWidth() - 700.0f, 20);
    }
    whermst::GetEngine().GetPT().Draw(renderer);
    _scene -> Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
_gameState = GameState::PlayerDead;
_stateTimer = 2.0f;
}
