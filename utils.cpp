#include "utils.hpp"

int loadTexture(const char * filename, GLuint * texture)
{
	SDL_Surface * bmp = NULL;

	if((bmp = SDL_LoadBMP(filename)) == NULL)
		return -1;

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bmp->w, bmp->h, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	SDL_FreeSurface(bmp);

	return 0;
}
