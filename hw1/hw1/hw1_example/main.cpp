#include "glut.h"
#include <iostream>

using namespace std;

void display();
void reshape(int _width, int _height);

int width = 400, height = 400;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("WindowName");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void display()
{
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5,5,-5,5,-5,5);
	//Viewport Matrix
	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();
	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}
