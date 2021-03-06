# COMP371 Group Project - Summer I 2017
Jeremy Brown -- ID 27515421
Devin Mens -- ID 26290515


## Features
- Fully moveable camera, with both mouse and keyboard input
- Fully modelled and textured room complex with independent lighting for each room
- Infinite depth illusion skybox
- Hot swappable shaders for 3D models

## Controls
- Toggling lights: Press `1`, `2`, or `3` to toggle lighting in that particular room.
- Toggling shaders: Press `T` to toggle between model shaders (Might have to retoggle lights after).
- X/Z Axis Camera movement: WASD, following typical movement scheme
- Camera orientation: Mouse movement following scheme similar to the one in common usage

## Code Usage
Certain code snippets were borrowed from [LearnOpenGL](https://learnopengl.com). These include the `Camera` class and the `Shader` class (equivalent to the template code given in the lab to read shader files). 

In addition to this, the `Model` and `Mesh` classes were used with the ASSIMP library to load object files.  

The objloader class was provided by the course lab code along with the skybox model

All furniture models were taken from the 3D warehouse section of the SketchUp program with proper attribution for each model provided in the project report


## Development Environment
The application can be built with [CMake](https://cmake.org).

You must have the [Conan Package Manager](https://www.conan.io) for `cmake` to install the required graphics libraries (GLFW, GLEW, GLM).

Two required libraries that are not present in conan package form must be installed manually first. 
1. libSOIL: On MacOS, a recommended method is described here: https://github.com/DeVaukz/SOIL.
2. Assimp: On MacOS, install with Homebrew (`brew install assimp`) or download and build here: https://github.com/assimp/assimp/.

The first time the project is built,
- Run `mkdir -p cmake-build-debug` to create the output directory.
- `cd` into the `cmake-build-debug` directory and run `conan install ../`.

** If you come across an issue where the error message resembles `cannot find library for -lGLEWd`, simply rename the `libGLEW.a` file downloaded by conan to `libGLEWd.a` (dirty fix).

All subsequent times, simply run  `cmake --build cmake-build-debug` to build the application.

The resulting binary will be located at `cmake-build-debug/bin/comp371-project`.

