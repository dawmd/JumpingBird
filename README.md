# JumpingBird
A clone of the popular game "[Flappy Bird](https://en.wikipedia.org/wiki/Flappy_Bird)" written in C++ using OpenGL.
The project is being done for educational purposes, mainly aiming at learning how to use third-party code and plan a bigger-scale project,
i.e. setting up a class hierarchy, deciding what tools to use, etc.

The program is still at the stage `Work in progress`, but it's runnable. The list of things I haven't implemented yet can be found below.

### Libraries required to run the program
* [GLEW](http://glew.sourceforge.net/)
* [GLFW3](https://www.glfw.org/)
* `libglfw3`
* `libglfw3-dev`
* `libglew-dev`
* `libgl1-mesa-dev`

The last four can be easily installed on Linux running `sudo apt-get install X` in the terminal, where `X` stands for the specific name of the packge.

### TODO
* Implementing collisions,
* Adding textures,
* Adding an end-game screen,
* Making a better interface for setting up the window's size,
* Displaying points in the game,
* Keeping the settings in a JSON file instead of asking the user to give them every time they run the game or using default ones.
