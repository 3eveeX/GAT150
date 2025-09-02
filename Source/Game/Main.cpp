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

#include "Platformer/PlatformerGame.h"




int main(int argc, char* argv[]) { 



	// set the current directory to the Assets folder
    whermst::file::SetCurrentDirectory("Assets/Platformer");
	whermst::Factory::Instance().Register<whermst::SpriteRenderer>("SpriteRenderer");
    
	auto spriteRenderer = whermst::Factory::Instance().Create<whermst::SpriteRenderer>("SpriteRenderer");
	spriteRenderer->name = "MySpriteRenderer";

	std::cout << argc << " arguments passed to the program." << std::endl;
    for (size_t i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
     
    }
  
    //initialize engine 
	whermst::GetEngine().Initialize();

    //initialize game
	std::unique_ptr<PlatformerGame> game = std::make_unique<PlatformerGame>();
	game->Initialize();

   //initialize font
	whermst::Font* font = new whermst::Font();
	font->Load("8bitOperatorPlus8-Regular.ttf", 20);

    

    SDL_Event e;
    bool quit = false;

    


    
   
  
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
       
        
        float speed = 200;
        whermst::vec2 direction{ 0, 0 };

        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1; 
        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
        if (whermst::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1; 

        if (direction.LengthSqr() > 0) { 
            direction = direction.Normalized();
        
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
