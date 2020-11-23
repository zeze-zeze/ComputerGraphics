#include "Object.h"
#include "glut.h"
#include <math.h>

int windowSize[2];

void light();
void display();
void reshape(GLsizei, GLsizei);
void LoadModel(Object*);
void DrawBasis();
void keyboard(unsigned char key, int x, int y);

Object* elephant = new Object("elephant.obj");
Object* cube = new Object("cube.obj");
Object* teapot = new Object("teapot.obj");
float d = 0;
int r = 0;

int degrees[2] = { 0, 0 }; // { (elephant, cube), basis } 
int width = 500, height = 500;
const float PI = 3.14159265;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	light();
	glutCreateWindow("HW1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void light()
{
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = { 50.0, 75.0, 80.0, 1.0 };
	glShadeModel(GL_SMOOTH);
	// z buffer enable
	glEnable(GL_DEPTH_TEST);
	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///TO DO Enable DepthTest
	///
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	///TO DO: add lighting, Viewport Matrix, Projection Matrix, ModelView Matrix
	///
	light();

	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, width / (GLfloat)height, 1.0, 1000);
	 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20.0f, 20.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	///TO DO: add model, translate, rotate, scale
	glTranslatef(0, d, 0);
	glRotatef(r, 1, 0, 0);
	
	glPushMatrix();
	glRotatef(degrees[1], 0, 1, 0);
	DrawBasis();

	glPushMatrix();
	glTranslatef(3, 0, -3);
	glRotatef(degrees[0], 0, 1, 0);
	glScalef(2, 2, 2);
	LoadModel(elephant);

	glTranslatef(-2, 0.5, -2);
	glScalef(0.5, 0.5, 0.5);
	LoadModel(cube);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 0, 3);
	LoadModel(teapot);
	glPopMatrix();

	glPopMatrix();
	glutPostRedisplay();
	glutSwapBuffers();

	degrees[0] += 3;
	degrees[1] += 1;
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadModel(Object* Model)
{
	for (size_t i = 0; i < Model->fNum; ++i)
	{
		glBegin(GL_TRIANGLES);
		for (size_t j = 0; j < 3; ++j)
		{
			glNormal3fv(Model->nList[Model->faceList[i][j].nIndex].ptr);
			glVertex3fv(Model->vList[Model->faceList[i][j].vIndex].ptr);
		}
		glEnd();
	}
}

void DrawBasis()
{
	///TO DO: draw basis
	///
	glPolygonMode(GL_FRONT, GL_FILL);  
	glPushMatrix();
	for (int i = 0; i < 20; i++) {
		glRotatef(18 * i, 0, 1, 0);
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 1, 0);
		
		glVertex3f(0, 0, 0);
		glVertex3f(10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(0, 0, 10 * sin(PI / 180 * 81));
		
		glVertex3f(0, 0, 0);
		glVertex3f(-10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(0, 0, 10 * sin(PI / 180 * 81));
		glEnd();

		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glVertex3f(10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(-10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(-10 * cos(PI / 180 * 81), -5, 10 * sin(PI / 180 * 81));
		glVertex3f(10 * cos(PI / 180 * 81), -5, 10 * sin(PI / 180 * 81));
		glEnd();
	}

	for (int i = 0; i < 20; i++) {
		glRotatef(-18 * i, 0, 1, 0);
		glBegin(GL_TRIANGLES);
		glNormal3f(0, 1, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(0, 0, 10 * sin(PI / 180 * 81));

		glVertex3f(0, 0, 0);
		glVertex3f(-10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(0, 0, 10 * sin(PI / 180 * 81));
		glEnd();

		glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glVertex3f(10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(-10 * cos(PI / 180 * 81), 0, 10 * sin(PI / 180 * 81));
		glVertex3f(-10 * cos(PI / 180 * 81), -5, 10 * sin(PI / 180 * 81));
		glVertex3f(10 * cos(PI / 180 * 81), -5, 10 * sin(PI / 180 * 81));
		glEnd();
	}
	glPopMatrix();
}

void keyboard(unsigned char key, int x, int y)
{
	/// TO DO: Set the keyboard control
	///
	switch (key)
	{
		case 'w':
			d += 1;
			break;
		case 's':
			d -= 1;
			break;
		case 'a':
			r -= 1;
			break;
		case 'd':
			r += 1;
	}
}