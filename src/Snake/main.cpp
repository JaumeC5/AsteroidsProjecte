#include "Renderer.hh"
#include "Window.hh"
#include "Sprite.hh"
#include "GameEngine.hh"
#include "InputManager.hh"
#include "Mob.hh"

int main(int argc, char* args[]) {
	srand(time(NULL));

	GameEngine g;
	g.Run();

	return 0;
}




