//util.cpp
#include <GL/glut.h>
#include "util.h"

void SetColor(Color color)
{
	switch (color) {
		case RED:		glColor3f(1.0, 0.0, 0.0); break;
		case BLUE:		glColor3f(0.0, 0.0, 1.0); break;
		case GREEN:		glColor3f(0.0, 1.0, 0.0); break;
		case CYAN: 		glColor3f(0.0, 1.0, 1.0); break;
		case MAGENTA:	glColor3f(1.0, 0.0, 1.0); break;
		case YELLOW:	glColor3f(1.0, 1.0, 0.0); break;
		case BLACK:		glColor3f(0.0, 0.0, 0.0); break;
		default:		glColor3f(0.5, 0.5, 0.5); break;
	}
}

void BitmapText(char *str, int wcx, int wcy, void *font, Color color)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);	// save the caller's set of attributes

	SetColor(color);
	glRasterPos2i(wcx, wcy);

	for (int i=0; str[i] != '\0'; i++) {
		glutBitmapCharacter(font, str[i]);
	}

	glPopAttrib();				// restore the caller's attributes
}

