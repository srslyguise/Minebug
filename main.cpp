#include <iostream>
#include <cmath>
#include <cstdlib>
#include "utils.hpp"
#include "cube.hpp"

#define PI 3.1415926535897932384626433832795028841971693993751058209749

using namespace std;

void doRender(void);
void doReshape(int, int);
void keyDown(SDLKey);
void keyUp(SDLKey);
void keys();
void mouseMotion(int, int);
void pointer();

int screenw, screenh;
int lastx, lasty;
bool grabbed = false;

float rotationy1 = 0.0;
float rotationy2 = 0.0;

double xdir, ydir, zdir;
double xcam, ycam, zcam;
double angley = 0.0;
double anglex = 90.0;
bool l, r, f, b;

GLuint textures[3];

GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};

int main(int argc, char ** argv)
{
	SDL_Surface * screen = NULL;
	SDL_Event e;
	bool end = false;

	if(SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		cout << "Impossibile inizializzare SDL: " << SDL_GetError() << endl;
        	exit(1);
    	}

	atexit(SDL_Quit);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE);

	if(screen == NULL)
	{
		cout << "Impossibile settare il video: " << SDL_GetError() << endl;
		exit(1);
	}

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	if(loadTexture("grass.bmp", &textures[0]) == -1)
		return -1;

	if(loadTexture("dirt.bmp", &textures[1]) == -1)
		return -1;

	textures[2] = textures[3] = textures[4] = textures[5] = textures[1];

	SDL_WM_SetCaption("Test", "Test");
	doReshape(640, 480);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	xdir = sin(anglex / 180 * PI) * sin(angley / 180 * PI);
	ydir = cos(anglex / 180 * PI);
	zdir = -sin(anglex / 180 * PI) * cos(angley / 180 * PI);
	xcam = 0.0;
	ycam = 3.0;
	zcam = 5.0;
	l = r = f = b = false;

	lastx = 320;
	lasty = 240;

	while(!end)
	{
		doRender();
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_KEYDOWN:
					keyDown(e.key.keysym.sym);
				break;

				case SDL_KEYUP:
					keyUp(e.key.keysym.sym);
				break;

				case SDL_MOUSEMOTION:
					mouseMotion(e.motion.x, e.motion.y);
				break;

				case SDL_VIDEORESIZE:
					screen = SDL_SetVideoMode(e.resize.w, e.resize.h, 32, SDL_HWSURFACE | SDL_OPENGL | SDL_RESIZABLE);
					doReshape(e.resize.w, e.resize.h);
				break;

				case SDL_QUIT:
					end = true;
				break;
			}
		}
		SDL_Delay(20);
	}
	
	glDeleteTextures(3, textures);
	SDL_FreeSurface(screen);

	return 0;
}

void pointer()
{
	glLoadIdentity(); //Reset camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPushMatrix();
	glOrtho(0, screenw, screenh, 0, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex2f(screenw/2 - 10, screenh/2);
		glVertex2f(screenw/2 + 10, screenh/2);
		glVertex2f(screenw/2, screenh/2 - 10);
		glVertex2f(screenw/2, screenh/2 + 10);		
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0 * screenw / screenh, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void doRender(void)
{
	Cube c1(2, textures);
	Cube c2(2, textures);
	Cube c3(2, textures);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	keys();
	gluLookAt(xcam, ycam, zcam, xcam + xdir, ycam + ydir, zcam + zdir, 0.0f, 1.0f,  0.0f);
	
	glPushMatrix();
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		for(float i = -100.0; i < 100.0; i += 0.5)
		{
			glVertex3f(i, 0.0f, -100.0f);
			glVertex3f(i, 0.0f, 100.0f);
			glVertex3f(-100.0f, 0.0f, i);
			glVertex3f(100.0f, 0.0f, i);
		}
		glColor3f(0, 1, 0);
		glVertex3f(0, -1000.0, 0);
		glVertex3f(0, 1000.0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(1.0, 1.0, -1.0);
	c1.Draw();
	glTranslatef(2.0, 0.0, 0.0);
	c2.Draw();
	glTranslatef(2.0, 0.0, 0.0);
	c3.Draw();
	glPopMatrix();

	pointer();

	SDL_GL_SwapBuffers();
}

void doReshape(int w, int h)
{
	screenw = w;
	screenh = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, 1.0 * w / h, 1.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
}

void keyDown(SDLKey key)
{
	if(key == SDLK_q)
		exit(0);

	if(key == SDLK_g)
	{
		if(grabbed == false)
		{
			SDL_WM_GrabInput(SDL_GRAB_ON);
			SDL_ShowCursor(false);
			grabbed = true;
		}
		else
		{
			SDL_WM_GrabInput(SDL_GRAB_OFF);
			SDL_ShowCursor(true);
			grabbed = false;
		}
	}

	if(key == SDLK_w)
		f = true;

	if(key == SDLK_s)
		b = true;

	if(key == SDLK_a)
		l = true;

	if(key == SDLK_d)
		r = true;
}

void keyUp(SDLKey key)
{
	if(key == SDLK_w)
		f = false;

	if(key == SDLK_s)
		b = false;

	if(key == SDLK_a)
		l = false;

	if(key == SDLK_d)
		r = false;
}

void keys()
{
	float fraction = 0.5;

	if(r)
	{
		xcam += fraction * -zdir;
		zcam += fraction * xdir;
	}
	if(l)
	{
		xcam -= fraction * -zdir;
		zcam -= fraction * xdir;
	}
	if(f)
	{
		xcam += fraction * xdir;
		ycam += fraction * ydir;
		zcam += fraction * zdir;
	}
	if(b)
	{
		xcam -= fraction * xdir;
		ycam -= fraction * ydir;
		zcam -= fraction * zdir;
	}
}

void mouseMotion(int x, int y)
{
	int diffx = x - lastx;
	int diffy = y - lasty;
	lastx = x;
	lasty = y;

	if(grabbed)
	{
		if(x <= 5)
		{
			lastx = x = screenw - 6;
			SDL_WarpMouse(x, y);
		}
		if(x >= (screenw - 5))
		{
			lastx = x = 6;
			SDL_WarpMouse(x, y);
		}
		if(y <= 5)
		{
			lasty = y = screenh - 6;
			SDL_WarpMouse(x, y);
		}
		if(y >= (screenh - 5))
		{
			lasty = y = 6;
			SDL_WarpMouse(x, y);
		}

		angley += diffx;
		anglex += diffy;

		if(anglex > 360)
			anglex = 0;

		if(angley > 360)
			angley = 0;

		if((anglex / 180 * PI) < 0.1)
			anglex -= diffy;

		if((anglex / 180 * PI) > (PI - 0.1))
			anglex -= diffy;

		xdir = sin(anglex / 180 * PI) * sin(angley / 180 * PI);
		ydir = cos(anglex / 180 * PI);
		zdir = -sin(anglex / 180 * PI) * cos(angley / 180 * PI);
	}
}
