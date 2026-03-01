#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdio.h>
#include <string>
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>

//Texture wrapper class
class LTexture
{
	public:
		LTexture();		//Initializes variables
		~LTexture();	//Deallocates memory
		
		bool loadFromFile( std::string path, SDL_Renderer* );	//Loads image at specified path
		
		//#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText(TTF_Font* Font, std::string textureText, SDL_Color textColor, SDL_Renderer* );
		//#endif
		
		void free();	//Deallocates texture
		void setColor( Uint8 red, Uint8 green, Uint8 blue );	//Set color modulation
		void setBlendMode( SDL_BlendMode blending );	//Set blending
		void setAlpha( Uint8 alpha );	//Set alpha modulation
		void render( int x, int y, SDL_Renderer*, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );	//Renders texture at given point

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;	//The actual hardware texture

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Loads media
bool loadMedia();

#endif