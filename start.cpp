#include "SDL2/SDL.h"
#include <iostream>

using std::cout;
using std::endl;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
	// The window we're rendering to.
	SDL_Window* window = nullptr;

	// Surface contained by the window.
	SDL_Surface* screenSurface = nullptr;

	// Initialize SDL

	if (SDL_Init( SDL_INIT_VIDEO) < 0 ) {
		cout << "SDL could not initialize! SDL_Error: " ;
		cout << SDL_GetError();
		cout << endl;
	}
	else {
		// create window
		window = SDL_CreateWindow( "Testing", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN );
		if (window == NULL) {
			cout << "Window could not be created! SDL_Error: ";
			cout << SDL_GetError() << endl;
		}
		else {
			// Get Window surface
			screenSurface = SDL_GetWindowSurface(window);

			// Fill the surface with white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(
				screenSurface->format, 0xFF,0xFF,0xFF) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );


			// Wait two seconds
			SDL_Delay( 2000 );
		}
	}

	// Destroy the window
	SDL_DestroyWindow( window);

	std::cout << "It worked!" << std::endl;

	// Quit SDL subsystems
	SDL_Quit();
	return 0;
}
