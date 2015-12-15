#include "SDL2/SDL.h"
#include <iostream>

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);
	std::cout << "It worked!" << std::endl;

	SDL_Quit();	
	return 0;
}
