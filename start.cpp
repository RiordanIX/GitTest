#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// startup SDL and create window
bool init();

// Frees media and shuts down SDL
void close();

// Loads media
bool loadMedia();

// Loads individual image as texture
SDL_Texture* loadTexture( string path );

// The window renderer
SDL_Renderer* gRenderer = nullptr;

// Current displayed texture
SDL_Texture* gTexture = nullptr;

// Loads individual image
SDL_Surface* loadSurface ( string path );

// The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

// Current displayed image
SDL_Surface* gCurrentSurface = nullptr;


// Main loop flag
bool quit = false;

// Event handler
SDL_Event e;

// global variables to be used in functions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we're rendering to
SDL_Window* gWindow = nullptr;

// The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;



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
            SDL_BlitSurface ( gCurrentSurface , NULL, gScreenSurface,
                NULL );
        }
    }

    // While the application is running
    while ( !quit ) {
        // Handle events on queue
        while ( SDL_PollEvent ( &e ) != 0 ) {
            // User requests quit
            if ( e.type == SDL_QUIT ) {
                quit = true;
            }
            // User presses a key
            else if( e.type == SDL_KEYDOWN ) {
                // Select surfaces based on key press
                switch( e.key.keysym.sym ) {
                    case SDLK_UP:
                    gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP];
                    break;

                    case SDLK_DOWN:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                    break;

                    case SDLK_LEFT:
                    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                    break;

                    case SDLK_RIGHT:
                    gCurrentSurface =gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                    break;

                    default:
                    gCurrentSurface=gKeyPressSurfaces[
                                                KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        SDL_BlitSurface ( gCurrentSurface , NULL, gScreenSurface, NULL );

        // Render red filled quad
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,
                            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect( gRenderer, &fillRect );

        // Render green outlined quad
        SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                            SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );

        // Draw blue horizontal line
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );

        SDL_RenderDrawLine( gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH,
                            SCREEN_HEIGHT / 2 );

        // Draw vertical line of yellow dots
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
        for( int i = 0; i < SCREEN_HEIGHT; i += 4 ) {
            SDL_RenderDrawPoint( gRenderer, SCREEN_WIDTH / 2, i );
        }
        SDL_RenderPresent( gRenderer );

        // Update the surface (draw to screen)
        SDL_UpdateWindowSurface ( gWindow );

    }

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
            // Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1,
                                             SDL_RENDERER_ACCELERATED );
            if( gRenderer == nullptr ) {
                cout << "Renderer could not be created! SDL Error: ";
                cout << SDL_GetError() << endl;
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );


                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    cout << "SDL_image could not initialize! SDL_image Error: ";
                    cout << IMG_GetError() << endl;
                    success = false;
                }
                else {
                    // Get window surface
                    gScreenSurface = SDL_GetWindowSurface( gWindow );
                }
            }
        }
    }

    return success;
}


// Loading media from image files
bool loadMedia() {
    // Loading success flag
    bool success = true;

    // Load PNG texture
    gTexture = loadTexture( "media/texture.png" );
    if( gTexture == nullptr) {
        cout << "Failed to load texture image!" << endl;
        success = false;
    }

    // Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface(
                                                    "media/default.bmp");
    if ( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == nullptr) {
        cout << "Unable to load image media/default.bmp" << endl;
        success = false;
    }

    // Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface(
                                                    "media/up.bmp");
    if ( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == nullptr) {
        cout << "Unable to load image media/up.bmp" << endl;
        success = false;
    }

    // Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface(
                                                    "media/down.bmp");
    if ( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == nullptr) {
        cout << "Unable to load image media/down.bmp" << endl;
        success = false;
    }

    // Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface(
                                                    "media/left.bmp");
    if ( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == nullptr) {
        cout << "Unable to load image media/left.bmp" << endl;
        success = false;
    }

    // Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface(
                                                    "media/right.bmp");
    if ( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == nullptr) {
        cout << "Unable to load image media/right.bmp" << endl;
        success = false;
    }

    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
    return success;
}



// release memory and end session
void close() {
    // Deallocate surface

    for (int i = KEY_PRESS_SURFACE_DEFAULT; i++; i < KEY_PRESS_SURFACE_TOTAL) {

        SDL_FreeSurface ( gKeyPressSurfaces[i] );
        gKeyPressSurfaces[i] = nullptr;
    }

    // Free and destroy texture
    SDL_DestroyTexture( gTexture );
    gTexture = nullptr;

    // Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    gRenderer = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


// Loads images into surfaces to be used
SDL_Surface* loadSurface( string path ) {
    // The final optimized image
    SDL_Surface* optimizedSurface = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == nullptr ) {
        cout << "Unable to load image " << path << "! SDL Error: ";
        cout << IMG_GetError() << endl;
    }
    else {
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadedSurface,
                                gScreenSurface->format, NULL );
        if ( optimizedSurface == nullptr ) {
            cout << "Unable to optimize image " << path << "! SDL Error: ";
            cout << SDL_GetError() << endl;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

SDL_Texture* loadTexture( string path ) {
    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr ) {
        cout << "Unable to load image " << path << "! SDL_Image Error: ";
        cout << IMG_GetError() << endl;
    }
    else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == nullptr ) {
            cout << "Unable to create texture from " << path << "! SDL Error:";
            cout << " " << SDL_GetError() << endl;
        }

        // Get rid of old loaded surfaces
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
