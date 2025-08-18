#include "EngineMinimal.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Engine.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"




int main(int argc, char* argv[]) { 



	// set the current directory to the Assets folder
    whermst::file::SetCurrentDirectory("Assets");
	whermst::Factory::Instance().Register<whermst::SpriteRenderer>("SpriteRenderer");

	auto spriteRenderer = whermst::Factory::Instance().Create<whermst::SpriteRenderer>("SpriteRenderer");
	spriteRenderer->name = "MySpriteRenderer";

	std::cout << argc << " arguments passed to the program." << std::endl;
    for (size_t i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
     
    }
    return 0;
    //initialize engine 
	whermst::GetEngine().Initialize();

    //initialize game
	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();

   //initialize font
	whermst::Font* font = new whermst::Font();
	font->Load("8bitOperatorPlus8-Regular.ttf", 20);

    //initialize Text
    //whermst::Text* text = new whermst::Text(font);
    //text->Create(whermst::GetEngine().GetRenderer(), "Hello World", whermst::vec3{1, 1, 1});

    //initialize image
	/*std::shared_ptr<whermst::Texture> texture = std::make_shared<whermst::Texture>();
    texture->Load("Eevee-Transparent-PNG.png", whermst::GetEngine().GetRenderer());*/
	//auto texture = whermst::Resources().Get<whermst::Texture>("Eevee-Transparent-PNG.png", whermst::GetEngine().GetRenderer());

    SDL_Event e;
    bool quit = false;

    //vec2 v(290, 300);

    whermst::GetEngine().GetAudio().Load("test.wav");
    whermst::GetEngine().GetAudio().Load("bass.wav", "bass");
    whermst::GetEngine().GetAudio().Load("clap.wav", "clap");
    whermst::GetEngine().GetAudio().Load("close-hat.wav", "close-hat");
    whermst::GetEngine().GetAudio().Load("cowbell.wav", "cowbell");
    whermst::GetEngine().GetAudio().Load("open-hat.wav", "open-hat");
    whermst::GetEngine().GetAudio().Load("snare.wav", "snare");
    whermst::GetEngine().GetAudio().Load("Laser.mp3", "laser");
    whermst::GetEngine().GetAudio().Load("explode.mp3", "Explode");
    whermst::GetEngine().GetAudio().Load("BGM.mp3", "bgm");
    whermst::GetEngine().GetAudio().Load("enemyHit.mp3", "enemyHit");
    whermst::GetEngine().GetAudio().Load("PlayerDeath.mp3", "playerdeath");


    //std::vector<whermst::vec2> points;
    //std::vector<std::vector<whermst::vec2>> confirmed;
    whermst::GetEngine().GetAudio().PlaySound("bgm");
    std::cout << "Playing BGM test" << std::endl;
  
    //MAIN LOOP
    while (!quit) {

        //update engine
		whermst::GetEngine().Update();
		game -> Update(whermst::GetEngine().GetTime().GetDeltaTime());
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            whermst::GetEngine().GetInput().HandleEvent(e);
        }
        //get input
        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
            quit = true;
        }
       /* if (input.GetKeyDown(SDL_SCANCODE_A)) audio.PlaySound("bass");
        if (input.GetKeyDown(SDL_SCANCODE_S)) audio.PlaySound("clap");
        if (input.GetKeyDown(SDL_SCANCODE_D)) audio.PlaySound("close-hat");
        if (input.GetKeyDown(SDL_SCANCODE_F)) audio.PlaySound("cowbell");
        if (input.GetKeyDown(SDL_SCANCODE_G)) audio.PlaySound("open-hat");
        if (input.GetKeyDown(SDL_SCANCODE_H)) audio.PlaySound("snare");*/
		//if (input.GetKeyDown(SDL_SCANCODE_A)) transform.rotation -= whermst::math::degToRad(45 * time.GetDeltaTime());
		//if (input.GetKeyDown(SDL_SCANCODE_D)) transform.rotation += whermst::math::degToRad(45 * time.GetDeltaTime());
        
        float speed = 200;
        whermst::vec2 direction{ 0, 0 };

        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1; 
        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1; 

        if (direction.LengthSqr() > 0) { 
            direction = direction.Normalized();
            //for (auto& actor : actors) {
              //  actor -> GetTransform().position += (direction * speed) * time.GetDeltaTime();
           // }
        
        }


        //draw
        whermst::vec3 colour(0, 0, 0);

		whermst::GetEngine().GetRenderer().SetColourf(colour.r, colour.g, colour.b); // Set the colour to black
        whermst::GetEngine().GetRenderer().Clear(); // Clear the renderer
        whermst::vec2 position = whermst::GetEngine().GetInput().GetMousePosition();
        //whermst::GetEngine().GetRenderer().DrawTexture(texture.get(), 300, 300, 90, 0.5f);

        whermst::GetEngine().GetRenderer().SetColourf(2, 0.3f, 1); // Set the colour to white

        //text->Draw(whermst::GetEngine().GetRenderer(), 40.0f, 40.0f);
		game->Draw(whermst::GetEngine().GetRenderer()); // Draw the game scene

       

       
        whermst::GetEngine().GetRenderer().Present(); // Render the screen
    }
	game->Shutdown(); // Shutdown the game
	game.release(); // Release the game object
	whermst::GetEngine().Shutdown(); // Shutdown the engine



    return 0;
}
