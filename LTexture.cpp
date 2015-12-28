// Texture wrapper class implementation

#include "LTexture.hpp"


// Initializes variables

LTexture::LTexture() {
    _Texture = nullptr;
    _Width = 0;
    _Height = 0;
    _Renderer = nullptr;
}


LTexture::LTexture(std::string path, SDL_Renderer* renderer) {
    _Renderer = renderer;
    loadFromFile( path );
}


LTexture::~LTexture() {
    // Deallocate
    free();
    _Renderer = nullptr;
}


bool LTexture::loadFromFile(
            std:: string path, SDL_Renderer* renderer = _Renderer ) {
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) {
        std::cout << "Unable to load image " << path << "! SDL_image Error: ";
        std::cout << IMG_GetError() << std::endl;
    }
    else {
        // Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( 
                loadedSurface->format, 0xFF, 0, 0xFF ) );
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL ) {
            std::cout << "Unable to create texture from " << path << "! ";
            std::cout << "SDl Error: " << SDL_GetError() << std::endl;
        }
        else {
            // Get image dimensions
            _Width = loadedSurface->w;
            _Height = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    // Return success
    _Texture = newTexture;
    return _Texture != nullptr;
}


void LTexture::free() {
    // Free texture if it exists
    if( _Texture != NULL ) {
        SDL_DestroyTexture( _Texture );
        _Texture = NULL;
        _Width = 0;
        _Height = 0;
    }
}


void LTexture::render( int x, int y, SDL_Renderer* renderer = _Renderer ) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, _Width, _Height };
    SDL_RenderCopy( renderer, _Texture, NULL, &renderQuad );
}




