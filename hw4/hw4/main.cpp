#define GLM_ENABLE_EXPERIMENTAL

#include "Object.h"
#include "FreeImage.h"
#include "glew.h"
#include "freeglut.h"
#include "shader.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <stb_image.h>
#include <ctime>
#include <chrono>

using namespace std;

void shaderInit();
void bindbufferInit(Object*, int);
void DrawLogo(GLuint);
void DrawTrike(GLuint);
void DrawUFO(GLuint);
void textureInit();
void display();
void idle();
void reshape(GLsizei w, GLsizei h);
void DrawUmbreon(GLuint);
void LoadTexture(unsigned int&, const char*);

GLuint UFOExplodeprogram, TrikeExplodeprogram, UFOprogram, Trikeprogram;
GLuint VAO[2], VBO[4];
unsigned int modeltexture, TrikeTexture, UFOTexture, LogoTexture, GreenBronzeTexture, MattoniBasamentoTexture, PavimentazioneTexture, DecorazioniMarmoTexture, PortaBronzoTexture;
float windowSize[2] = { 600, 600 };
float UFOangle = 0.0f, Trikeangle = 0.0f, Triketranslate = -15;
float explosion = 0.0;
int start = 0;
glm::vec3 WorldLightPos = glm::vec3(0, 0, 5);
glm::vec3 WorldCamPos = glm::vec3(0, 0, 5);

Object* UFOmodel = new Object("UFO_Empty.obj");
Object* Trikemodel = new Object("Intergalactic_Spaceship-(Wavefront).obj");

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(windowSize[0], windowSize[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("UFO vs Spaceship");

	glewInit();
	shaderInit();
	bindbufferInit(UFOmodel, 0);
	bindbufferInit(Trikemodel, 1);
	textureInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void shaderInit() {
	GLuint vert = createShader("Shaders/trike.vert", "vertex");
	GLuint goem = createShader("Shaders/trike.geom", "geometry");
	GLuint frag = createShader("Shaders/trike.frag", "fragment");
	Trikeprogram = createProgram(vert, 0, frag);

	vert = createShader("Shaders/UFO.vert", "vertex");
	goem = createShader("Shaders/UFO.geom", "geometry");
	frag = createShader("Shaders/UFO.frag", "fragment");
	UFOprogram = createProgram(vert, 0, frag);

	vert = createShader("Shaders/trikeexplode.vert", "vertex");
	goem = createShader("Shaders/trikeexplode.geom", "geometry");
	frag = createShader("Shaders/trikeexplode.frag", "fragment");
	TrikeExplodeprogram = createProgram(vert, goem, frag);

	vert = createShader("Shaders/UFOexplode.vert", "vertex");
	goem = createShader("Shaders/UFOexplode.geom", "geometry");
	frag = createShader("Shaders/UFOexplode.frag", "fragment");
	UFOExplodeprogram = createProgram(vert, goem, frag);
}

void bindbufferInit(Object* model, int index) {
	glGenVertexArrays(1, &VAO[index]);
	glGenBuffers(4, VBO);

	glBindVertexArray(VAO[index]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->positions[0]) * model->positions.size(), &model->positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->normals[0]) * model->normals.size(), &model->normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model->texcoords[0]) * model->texcoords.size(), &model->texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void textureInit() {
	LoadTexture(UFOTexture, "UFO_rough.jpg");
	LoadTexture(TrikeTexture, "Intergalactic Spaceship_metalness.jpg");
}

glm::mat4 getV()
{
	// set camera position and configuration
	return glm::lookAt(glm::vec3(WorldCamPos.x, WorldCamPos.y, WorldCamPos.z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

glm::mat4 getP()
{
	// set perspective view
	float fov = 45.0f;
	float aspect = windowSize[0] / windowSize[1];
	float nearDistance = 1.0f;
	float farDistance = 100.0f;
	return glm::perspective(glm::radians(fov), aspect, nearDistance, farDistance);
}

void display() {
	//Clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawUFO(UFOprogram);
	DrawUFO(UFOExplodeprogram);
	DrawTrike(Trikeprogram);
	DrawTrike(TrikeExplodeprogram);
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	windowSize[0] = w;
	windowSize[1] = h;
}

void LoadTexture(unsigned int& texture, const char* tFileName) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(tFileName, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void idle() {
	glutPostRedisplay();
}

void DrawUFO(GLuint program) {
	glUseProgram(program);
	if (explosion < 50 && start) explosion += 0.001;
	glm::mat4 M(1.0f);
	/*M = glm::rotate(M, glm::radians(90.0f), glm::vec3(1, 0, 0));
	M = glm::scale(M, glm::vec3(0.3, 0.3, 0.3));*/
	UFOangle += 0.01;
	M = glm::translate(M, glm::vec3(0, 1, -1));
	M = glm::rotate(M, glm::radians(UFOangle), glm::vec3(0, 1, 0));

	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

	glm::mat4 V = getV();
	ModelMatrixID = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &V[0][0]);

	glm::mat4 P = getP();
	ModelMatrixID = glGetUniformLocation(program, "P");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &P[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, UFOTexture);
	glUniform1i(glGetUniformLocation(program, "UFOTexture"), 0);

	GLuint startID = glGetUniformLocation(program, "start");
	glUniform1i(startID, start);

	GLuint explosionID = glGetUniformLocation(program, "explosion");
	glUniform1f(explosionID, explosion);

	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3 * UFOmodel->fNum);
	glBindVertexArray(0);
	glActiveTexture(0);
	glUseProgram(0);
}

void DrawTrike(GLuint program) {
	glUseProgram(program);

	glm::mat4 M(1.0f);
	Trikeangle += 0.1;
	Triketranslate += 0.002;
	if (Triketranslate > 0) start = 1;
	M = glm::scale(M, glm::vec3(0.1, 0.1, 0.1));
	M = glm::translate(M, glm::vec3(0, Triketranslate, 0));
	M = glm::rotate(M, glm::radians(Trikeangle), glm::vec3(1, 1, 0));

	GLuint ModelMatrixID = glGetUniformLocation(program, "M");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);

	glm::mat4 V = getV();
	ModelMatrixID = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &V[0][0]);

	glm::mat4 P = getP();
	ModelMatrixID = glGetUniformLocation(program, "P");
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &P[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TrikeTexture);
	glUniform1i(glGetUniformLocation(program, "TrikeTexture"), 0);

	GLuint startID = glGetUniformLocation(program, "start");
	glUniform1i(startID, start);

	GLuint explosionID = glGetUniformLocation(program, "explosion");
	glUniform1f(explosionID, explosion);

	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3 * Trikemodel->fNum);
	glBindVertexArray(0);
	glActiveTexture(0);
	glUseProgram(0);
}