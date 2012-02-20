#include "cube.hpp"

void Cube::Draw()
{
	float span = side / 2;

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(span, span, span);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(span, span, -span);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-span, span, -span);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-span, span, span);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(span, -span, span);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(span, -span, -span);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-span, -span, -span);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-span, -span, span);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(span, span, span);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(span, span, -span);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(span, -span, -span);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(span, -span, span);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-span, span, span);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-span, span, -span);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-span, -span, -span);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-span, -span, span);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(span, span, span);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-span, span, span);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-span, -span, span);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(span, -span, span);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(span, span, -span);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-span, span, -span);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-span, -span, -span);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(span, -span, -span);
	glEnd();
}
