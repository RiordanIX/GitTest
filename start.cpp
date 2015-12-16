#include "SDL2/SDL.h"
#include <iostream>

using std::cout;
using std::endl;

// startup SDL and create window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();



// global variables to be used in functions 
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we're rendering to
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

// The image we will load and show on the screen
SDL_Surface* gHelloWorld = nullptr;



int main ( int argc, char* args[] ) {
	//Startup SDL and create window
	if ( !init() ) {
		cout << "Failed to initialize!" << endl;
	}
	else {
		if ( !loadMedia()) {
			cout << "Failed to load media!" << endl;
		}
		else {
			// Apply the image
			SDL_BlitSurface ( gHelloWorld, NULL, gScreenSurface,
				NULL );
		}
	}

	// Update the surface (draw to screen)
	SDL_UpdateWindowSurface ( gWindow );

	// Wait a few seconds
	SDL_Delay ( 5000 );

	// end the session and free resources
	close();
	return 0;
}


bool init() {
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
		cout << "SDL could not initialize! SDL_Error: ";
		cout << SDL_GetError() << endl;
		success = false;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow( "Testing", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN );
		if ( gWindow == nullptr ) {
			cout << "Window could not be created! SDL_Error: ";
			cout << SDL_GetError();
			success = false;
		}
		else {
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}


// Loading media from image files
bool loadMedia() {
	// Loading success flag
	bool success = true;

	// Load splash image
	gHelloWorld = SDL_LoadBMP( "media/preview.bmp" );
	if ( gHelloWorld == nullptr) {
		cout << "Unable to load image media/preview.png" << endl;
		success = false;
	}

	return success;
}



// release memory and end session
void close() {
	// Deallocate surface
	SDL_FreeSurface ( gHelloWorld );
	gHelloWorld = nullptr;

	// Destroy window
	SDL_DestroyWindow ( gWindow );
	gWindow = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}

