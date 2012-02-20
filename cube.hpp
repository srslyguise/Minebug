#ifndef CUBE_HPP
#define CUBE_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class Cube
{
	public:
		Cube() : side(1), textures(NULL){}
		Cube(float s, GLuint * t) : side(s), textures(t){}
		void Draw();
	private:
		float side;
		GLuint * textures;
};

#endif
