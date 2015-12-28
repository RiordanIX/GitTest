#ifndef LTEXTURE_HPP
#define LTEXTURE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>




// Texture wrapper class
class LTexture
{
public:
	// Initialize variables
	LTexture();
	LTexture( std::string path );

	// Deallocates memory
	~LTexture();

	// Loads image from specified path
	bool loadFromFile( std::string path );

	// Deallocates the texture
	void free();

	// Renders texture at a given point
	// Optionally can have a different renderer passed in.
	void render( int x, int y , SDL_Renderer* renderer = _Renderer);

	// Changes the rendering target internally
	void setRenderer( SDL_Renderer* renderer) { _Renderer = renderer };

	// Retrieves image dimensions
	int getWidth() {  return _Width;  }
	int getHeight() { return _Height; }

private:
	// The actual hardware texture
	SDL_Texture* _Texture;

	// An internal copy of the renderer. Prevents it being passed everytime.
	SDL_Renderer* _Renderer;

	// Image dimensions
	int _Width;
	int _Height;
};



#endif // LTEXTURE_HPP
