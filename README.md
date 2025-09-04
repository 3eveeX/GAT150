Whermst Game Engine
Project Overview

Whermst is a lightweight C++ game engine designed for 2D game development. The repository includes the engine itself as well as several example games that demonstrate how to use its core systems. Whermst provides developers with the tools to handle rendering, input, physics, audio, and data serialization, allowing for rapid prototyping of small games while serving as a foundation for more complex projects.

Core Features

Engine Core:

Scene and Actor system for modular game object management

Core game loop (update and draw cycles)

Input handling for keyboard and mouse

2D rendering support (sprites, textures, fonts, colors)

Basic physics integration via Box2D

Audio playback and management via FMOD

Data serialization with RapidJSON for saving/loading game states

Extra Features / Additions:

Multiple example games showcasing engine functionality

Resource management for efficient loading and handling of assets

Simple collision detection and physics interactions

Audio effects and background music integration

Cross-platform build support via CMake (Linux/macOS) and Visual Studio 2022 (Windows)

Screenshots

<img width="425" height="1184" alt="image" src="https://github.com/user-attachments/assets/ae962d5d-198d-49c0-a52c-8c4b4894b949" />
<img width="1159" height="573" alt="image" src="https://github.com/user-attachments/assets/a63a86f3-b7ce-45c0-bb16-90f518b6d821" />
<img width="334" height="849" alt="image" src="https://github.com/user-attachments/assets/ad9227e4-75e4-475a-a5f0-51755cd60c61" />








Building and Running

Windows (Visual Studio 2022):

Clone the repository:

git clone https://github.com/3eveeX/GAT150.git
cd GAT150


Open the solution in Visual Studio 2022.

Ensure SDL3, Box2D, FMOD, and RapidJSON include and library directories are set in project properties.

Build the solution (Ctrl+Shift+B) and run one of the example games (F5).

Linux/macOS (CMake):

git clone https://github.com/3eveeX/GAT150.git
cd GAT150
mkdir build
cd build
cmake ..
cmake --build .


Make sure SDL3, Box2D, RapidJSON are installed and FMOD is linked manually.

Known Issues / Limitations

No UI system currently; no menus or HUDs implemented.

Input mapping is basic; key rebinding not supported.

FMOD integration may require manual setup depending on platform.

Engine is primarily designed for 2D games; 3D support is limited.

Credits / External Libraries

SDL3
 – graphics, windowing, input

Box2D
 – physics engine

FMOD
 – audio system

RapidJSON
 – JSON parsing and serialization

Example games and assets were created by 3eveeX
