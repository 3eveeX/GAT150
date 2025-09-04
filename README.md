Whermst Game Engine

Whermst is a lightweight C++ game engine built as part of coursework and personal development. It provides the fundamental systems needed to create 2D games, including rendering, input handling, asset management, physics, and audio. The repository also includes several small example games that demonstrate how to use the engine in practice. While originally created as a learning project, it serves as a solid foundation for building simple games or expanding into larger projects.

The engine uses SDL3
 for graphics and window management, Box2D
 for physics, FMOD
 for audio, and RapidJSON
 for serialization. Together these libraries provide a flexible environment for building interactive experiences with support for rendering sprites, handling collisions, simulating movement, and playing both 2D and 3D audio. The codebase follows a scene/actor architecture, letting you extend behaviour by creating your own game objects with Update and Draw methods.

The project can be built and run directly in Visual Studio 2022 on Windows, with SDL3, Box2D, FMOD, and RapidJSON linked through project settings. It can also be built with CMake on Linux or macOS, provided the dependencies are installed. Once compiled, the included example games can be run to see the engine in action, and new games can be created by extending the existing actor system and integrating physics and audio where needed.

This engine was developed primarily by 3eveeX
, guided by coursework and professor instruction, with thanks to the open-source libraries it depends on. At present, no license has been applied, so outside use is restricted. Future plans include adding UI support, input mapping, and more polished demo games, making Whermst not just a learning tool but a fully featured platform for small-scale game development.
