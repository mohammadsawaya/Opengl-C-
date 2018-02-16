// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
#include <math.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
// Achtung, die OpenGL-Tutorials nutzen glfw 2.7, glfw kommt mit einem veränderten API schon in der Version 3 
// Befindet sich bei den OpenGL-Tutorials unter "common"
#include "shader.hpp"
// Wuerfel und Kugel texture Obj3d 
#include "objects.hpp"
#include "objloader.hpp"
#include "texture.hpp"
#include "CGTutorial.h"
#include "Obj3D.h"
bool geschwindig = false;
float gvalue = 0.0f;
float xForEarth1, yForEarth1, xForEarth2, yForEarth2, xForEarth3, yForEarth3, xForEarth4, yForEarth4, xForEarth5, yForEarth5, xForEarth6, yForEarth6, xForEarth7, yForEarth7, xForEarth8, yForEarth8, xForEarth9, yForEarth9;
float counterForEarth1, counterForEarth2, counterForEarth3, counterForEarth4, counterForEarth5, counterForEarth6, counterForEarth7, counterForEarth8, counterForEarth9 = 0.0;
float camer_left_Right_Rot = 0.0f;
float camer_Up_Dawn_Rot = 0.0f;
float camera_Position_Z = -55.0f;
float camera_Position_X = 0.0f;
float camera_Position_Y = -34.0f;

float angleX = 5.0f;
float angleY = 0.0f;
float angleZ = 0.0f;
								// speed alle Planeten around the Sun
float plantetRotet = 0.1f;
float plantetRotet1 = 0.0f;		
float plantetRotet2 = 0.0f;
float plantetRotet3 = 0.0f;
float plantetRotet4 = 0.0f;
float plantetRotet5 = 0.0f;
float plantetRotet6 = 0.0f;
float plantetRotet7 = 0.0f;
float plantetRotet8 = 0.0f;
float MoonRotet = 0.2f;					// speed of moon arouond the Earth
float MoonRotet_finster = 0.0f;			//speed in case kosof
int viewRotate = 0;							// zu bestimmung welche Planet betrachtet wird !
float viewrotatespeed = 0.0f;			//für wechselung der Geschwindigkeit Drehunug von View (Camera Matrix)  

float Merkur = 40.0f;					// Standard Size (hier the small one is Merkur ) and then with it compiling
bool finster = true;						// um zu wechsel zu Sonnenfinsternis Zustand
bool moonfenster = true;					// um zu wechsel zu Mondfisternis Zustand

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_X:			// rotete the view on X
		angleX = angleX + 1.0f;  viewRotate = 0;
		break;
	case GLFW_KEY_Y:			// rotete the view on Y
		angleY = angleY + 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_Z:			// rotete the view on Z
		angleZ = angleZ + 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_S:				//Move camera z-achse Out
		camera_Position_Z -= 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_W:				//Move camera z-achse in
		camera_Position_Z += 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_J:				//Move camera x-achse links
		camera_Position_X -= 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_L:				//Move camera x-achse  rechts
		camera_Position_X += 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_K:				//Move camera down y-achse
		camera_Position_Y -= 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_I:				//Move camera   up y achse
		camera_Position_Y += 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_A:				//camera rotate links
			camer_left_Right_Rot -= 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_D:				//camera rotate rechts 
			camer_left_Right_Rot += 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_Q:				//camera rotate up
			camer_Up_Dawn_Rot -= 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_E:				//camera rotate dowun 
			camer_Up_Dawn_Rot += 1.0f; viewRotate = 0;
		break;
	case GLFW_KEY_1:					// die erste Planet betrachtet	
		finster = true;
		camera_Position_X = 5.5f;
		camera_Position_Y = -3.5f;
		camera_Position_Z = -3.0f;
		camer_left_Right_Rot = 5.0f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 1; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_2:				//die zwite Planet betrachtet	
		finster = true;
		camera_Position_X = 7.7f;
		camera_Position_Y = -3.5f;
		camera_Position_Z = -3.0f;
		camer_left_Right_Rot = 7.5f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 2; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_3:					//die dritte Planet betrachtet	
		finster = true;
		camera_Position_X = 10.4f;
		camera_Position_Y = -3.5f;
		camera_Position_Z = -2.8f;
		camer_left_Right_Rot = 10.0f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 3; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_4:				// die vierte Planet betrachtet	
		finster = true;
		camera_Position_X = 13.5f;
		camera_Position_Y = -3.5f;
		camera_Position_Z = -2.8f;
		camer_left_Right_Rot = 13.0f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 4; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_5:					// die fünfte Planet betrachtet	
		finster = true;
		camera_Position_X = 19.0f;
		camera_Position_Y = -4.5f;
		camera_Position_Z = -3.0f;
		camer_left_Right_Rot = 18.5f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 5; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_6:					// die sechste Planet betrachtet	
		finster = true;
		camera_Position_X = 24.7f;
		camera_Position_Y = -4.0f;
		camera_Position_Z = -3.0f;
		camer_left_Right_Rot = 24.5f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 6; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_7:					//die siebte Planet betrachtet	
		finster = true;
		camera_Position_X =29.5f;
		camera_Position_Y = -3.0f;
		camera_Position_Z = -2.0f;
		camer_left_Right_Rot = 29.5f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 7; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_8:						// achte Planet betrachtet	
		finster = true;
		camera_Position_X = 32.5f;
		camera_Position_Y = -3.0f;
		camera_Position_Z = -2.0f;
		camer_left_Right_Rot = 32.5f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 8; angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_ENTER:							// zurück zu Startstand
		finster = true;
		camera_Position_X = 0.0f;
		camera_Position_Y = -34.0f;
		camera_Position_Z = -48.1f;
		camer_left_Right_Rot = 0.0f;
		camer_Up_Dawn_Rot = 0.0f;
		viewRotate = 0;
		angleX = 5.0f; angleY = 0.0f; angleZ = 0.0f;
		break;
	case GLFW_KEY_9:							//die Mondfinsternis ....
		if (finster)
			{finster = false;}
			moonfenster = true;
			camera_Position_X = 7.0f;
			camera_Position_Y = -4.0f;
			camera_Position_Z = -16.0f;
			camer_left_Right_Rot = 10.0f;
			camer_Up_Dawn_Rot = 0.0f;
			angleX = 25.0f;
			viewRotate = 0;
		break;
	case GLFW_KEY_0:							//die Sonnefinsternis ...
		if (finster)
		{finster = false;}
		moonfenster = false;
		camera_Position_X = 7.0f;
		camera_Position_Y = -4.0f;
		camera_Position_Z = -16.0f;
		camer_left_Right_Rot = 10.0f;
		camer_Up_Dawn_Rot = 0.0f;
		angleX = 25.0f;
		viewRotate = 0;
		break;
	case GLFW_KEY_UP:							// Anstieg die geschwindigkeit 
		if (!geschwindig)
			geschwindig = true;
		gvalue += 0.01;
		break;
	case GLFW_KEY_DOWN:							// senken die Geschwindigkeit 
		if (geschwindig)
			geschwindig = false;
		gvalue -= 0.01;
		break;
	default:
		break;
	}
}

// Diese Drei Matrizen global (Singleton-Muster), damit sie jederzeit modifiziert und
// an die Grafikkarte geschickt werden koennen
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
GLuint programID;

void sendMVP()
{
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; 
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform, konstant fuer alle Eckpunkte
	glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);
}
// we need the circel for the Orbit of the Planets 
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	float PI = 3.141592;
	int lineAmount = 100; //# of triangles used to draw circle

 //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;	
	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		
		glVertex3f(
			x + (radius * cos(i *  twicePi / lineAmount)), 0.0f,
			y+ (radius* sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}
//zeichnen die kreisen um Saturn planet 
void drawHollowCircleRing() {
	int i = 0;
	float arad=34.0;
	for (i; i < 100; i++) {
		arad += 0.1;
		drawHollowCircle(0.0, 0.0, arad);
	}
}

// Die Bahnen zeichnen
void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;
	float DEG2RAD = 3.14159 / 180.0;
	float x = 1;//we start at angle = 0 
	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		//apply radius and offset
		glVertex3f(x * rx + cx,0.0f , y * ry + cy);//output vertex 
									 //apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
	
}
// un die bestimmen x und z punkten für dei Umdrehung
void rotateOnOrbit(int num, float dx, float dy) {
	float DEG2RAD = 3.14159 / 180.0;
	if (num == 1) {
		if (counterForEarth1 > 359)
			counterForEarth1 = 0;//reset to 0 when becomes 360
		else
			counterForEarth1 += 0.06;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth1 = cos(counterForEarth1*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth1 = sin(counterForEarth1*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 2) {
		if (counterForEarth2 > 359)
			counterForEarth2 = 0;//reset to 0 when becomes 360
		else
			counterForEarth2 += 0.038;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth2 = cos(counterForEarth2*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth2 = sin(counterForEarth2*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 3) {
		if (counterForEarth3 > 359)
			counterForEarth3 = 0;//reset to 0 when becomes 360
		else
			counterForEarth3 += 0.02;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth3 = cos(counterForEarth3*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth3 = sin(counterForEarth3*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 4) {
		if (counterForEarth4 > 359)
			counterForEarth4 = 0;//reset to 0 when becomes 360
		else
			counterForEarth4 += 0.01;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth4 = cos(counterForEarth4*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth4 = sin(counterForEarth4*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 5) {
		if (counterForEarth5 > 359)
			counterForEarth5 = 0;//reset to 0 when becomes 360
		else
			counterForEarth5 += 0.00236;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth5 = cos(counterForEarth5*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth5 = sin(counterForEarth5*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 6) {
		if (counterForEarth6 > 359)
			counterForEarth6 = 0;//reset to 0 when becomes 360
		else
			counterForEarth6 += 0.00059;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth6 = cos(counterForEarth6*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth6 = sin(counterForEarth6*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 7) {
		if (counterForEarth7 > 359)
			counterForEarth7 = 0;//reset to 0 when becomes 360
		else
			counterForEarth7 += 0.0000168;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth7 = cos(counterForEarth7*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth7 = sin(counterForEarth7*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 8) {
		if (counterForEarth8 > 359)
			counterForEarth8 = 0;//reset to 0 when becomes 360
		else
			counterForEarth8 += 0.00000329;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth8 = cos(counterForEarth8*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth8 = sin(counterForEarth8*DEG2RAD)*dy;//to change the y co-ordinate
	}
	else if (num == 9) {
		if (counterForEarth9 > 359)
			counterForEarth9 = 0;//reset to 0 when becomes 360
		else
			counterForEarth9 += 0.02;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

		xForEarth9 = cos(counterForEarth9*DEG2RAD)*dx;//to change the x co-ordinate
		yForEarth9 = sin(counterForEarth9*DEG2RAD)*dy;//to change the y co-ordinate
	}
}
// Alle Planeten drehen , schiepen und scalieren 
void planetDrehung(float x, float gross, float rotationSpeed) { // x : ist die Entfernung von der Sonne , gross für dir Große der Planet  , rotationspeed für die Bestimmung der Geschwindigkeit einer Planet.
	glm::mat4 Save = Model;
	
	Model = glm::rotate(Model, rotationSpeed, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around the sun
	Model = glm::translate(Model, glm::vec3(x, 0, 0));// move to the place 
	Model = glm::scale(Model, glm::vec3(1.0 / (Merkur-gross), 1.0 / (Merkur - gross), 1.0 / (Merkur - gross)));//´sitteing the size 
	Model = glm::rotate(Model, plantetRotet, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around selfe
	sendMVP();
}
// Umdrehung funktion auf die ovale Bahnen
void planetDrehung1(float x,float z, float gross, float rotationSpeed) { // x : ist die Entfernung von der Sonne , gross für dir Große der Planet  , rotationspeed für die Bestimmung der Geschwindigkeit einer Planet.
	glm::mat4 Save = Model;
	Model = glm::rotate(Model, rotationSpeed, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around the sun
	Model = glm::translate(Model, glm::vec3(x, 0, z));// move to the place 
	Model = glm::scale(Model, glm::vec3(1.0 / (Merkur - gross), 1.0 / (Merkur - gross), 1.0 / (Merkur - gross)));//´sitteing the size 
	Model = glm::rotate(Model, plantetRotet, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around selfe
	sendMVP();
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}
	// Fehler werden auf stderr ausgegeben, s. o.
	glfwSetErrorCallback(error_callback);
	// Open a window and create its OpenGL context
	// glfwWindowHint vorher aufrufen, um erforderliche Resourcen festzulegen
	GLFWwindow* window = glfwCreateWindow(2024, // Breite1024
										  1768,  // Hoehe768
										  "CG -Solar System", // Ueberschrift
										  NULL,  // windowed mode
										  NULL); // shared windoe
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Make the window's context current (wird nicht automatisch gemacht)
    glfwMakeContextCurrent(window);
	// Initialize GLEW
	// GLEW ermöglicht Zugriff auf OpenGL-API > 1.1
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	// Auf Keyboard-Events reagieren
	glfwSetKeyCallback(window, key_callback);
	// Schwarz background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	// Shader auch benutzen !
	glUseProgram(programID);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(glGetUniformLocation(programID, "myTextureSun"), 0);
	glUniform1i(glGetUniformLocation(programID, "myTextureJupiter"), 1);
	glUniform1i(glGetUniformLocation(programID, "myTextureMars"), 2);
	glUniform1i(glGetUniformLocation(programID, "myTextureNeptune"), 3);
	glUniform1i(glGetUniformLocation(programID, "myTextureSaturn"), 4);
	glUniform1i(glGetUniformLocation(programID, "myTextureUranus"), 5);
	glUniform1i(glGetUniformLocation(programID, "myTextureMercury"), 6);
	glUniform1i(glGetUniformLocation(programID, "myTextureVenus"), 7);
	glUniform1i(glGetUniformLocation(programID, "myTextureEarth"), 8);
	glUniform1i(glGetUniformLocation(programID, "myTextureMoon"), 9);
	glUniform1i(glGetUniformLocation(programID, "myTextureStarsMap"), 10);
	// Load  texture
	GLuint Texture0 = loadBMP_custom("Bilder/sun.bmp");
	GLuint Texture5 = loadBMP_custom("Bilder/jupitar.bmp");
	GLuint Texture4 = loadBMP_custom("Bilder/mars.bmp");
	GLuint Texture8 = loadBMP_custom("Bilder/neptune.bmp");
	GLuint Texture6 = loadBMP_custom("Bilder/saturn.bmp");
	GLuint Texture7 = loadBMP_custom("Bilder/uranus.bmp");
	GLuint Texture1 = loadBMP_custom("Bilder/mercury.bmp");
	GLuint Texture2 = loadBMP_custom("Bilder/venus.bmp");
	GLuint Texture3 = loadBMP_custom("Bilder/earth.bmp");
	GLuint Texture9 = loadBMP_custom("Bilder/moon.bmp");
	GLuint Texture10 = loadBMP_custom("Bilder/StarsMap.bmp");
	// load das KugelObjekt
	Obj3D earth("earth.obj");
	// Eventloop
	while (!glfwWindowShouldClose(window))
	{
		// Clear the screen
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
			// für Erhöhung und  Reduzierung der Geschwindigkeit 
			 counterForEarth1 += gvalue; counterForEarth2 += gvalue; counterForEarth3 += gvalue; counterForEarth4 += gvalue; counterForEarth5 += gvalue; counterForEarth6 += gvalue;
			 counterForEarth7 += gvalue; counterForEarth8 += gvalue; counterForEarth9 += gvalue;

		 plantetRotet   += 0.02f;							// Planeten deehen um sich    
		 plantetRotet1  += 0.00004f;						//Merkur alle 4 Monaten
		 plantetRotet2 +=  0.00004f;						//venus  alle 7 M
		 plantetRotet3 +=  0.00004f;						//die Erde all 12 M
		 plantetRotet4 +=  0.00004f;						//Mars  alle 23 M.
		 plantetRotet5 +=  0.00004f;						//Jupiter alle 142 M.
		 plantetRotet6 +=  0.00004f;						//satorn	alle 354 M.
		 plantetRotet7 +=  0.00004f;						//uranus	alle 1009 M.
		 plantetRotet8 +=  0.00004f;						//neptune alle 1979 M.
		 MoonRotet += 0.00004f;						    	// increse the speed for the Moon all time
		 MoonRotet_finster -= 0.00000001f;					
		 // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		 Projection = glm::perspective(80.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		// Camera matrix
		View = glm::lookAt(glm::vec3(camera_Position_X,camera_Position_Y,camera_Position_Z),  // Camera is at (0,0,-5), in World Space
						   glm::vec3(camer_left_Right_Rot,camer_Up_Dawn_Rot,0),				  // and looks at the origin
						   glm::vec3(0,-1,0));											   	  // Head is up (set to 0,-1,0 to look upside-down)
		// if else um die Bestimmung , welcher Planet betrachtet wird
			 if (viewRotate == 1) View = glm::rotate(View, counterForEarth1, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (viewRotate == 2) View = glm::rotate(View, counterForEarth2, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (viewRotate == 3) View = glm::rotate(View, counterForEarth3, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (viewRotate == 4) View = glm::rotate(View, counterForEarth4, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (viewRotate == 5) View = glm::rotate(View, counterForEarth5, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (viewRotate == 6) View = glm::rotate(View, counterForEarth6, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (viewRotate == 7) View = glm::rotate(View, counterForEarth7, glm::vec3(0.0f, 1.0f, 0.0f));
		else if (viewRotate == 8) View = glm::rotate(View, counterForEarth8, glm::vec3(0.0f, 1.0f, 0.0f));
		else viewrotatespeed = 0.0f; View = glm::rotate(View, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		// Model matrix : an identity matrix (model will be at the origin)
		Model = glm::mat4(1.0f);
		Model = glm::rotate(Model, angleX, glm::vec3(1.0f, 0.0f, 0.0f));			// Drehen die ganze szene um die X-Achse
		Model = glm::rotate(Model, angleY, glm::vec3(0.0f, 1.0f, 0.0f));			// Drehen die ganze szene um die Y-Achse
		Model = glm::rotate(Model, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));			// Drehen die ganze szene um die Z-Achse
		glm::mat4 Save = Model;
		Model = glm::scale(Model, glm::vec3(3.5f , 3.5f, 3.5f));
		if (finster) {
			glm::vec3 lightPos = glm::vec3(0, 0, 0);
			glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace1"), lightPos.x, lightPos.y, lightPos.z);
			sendMVP();
			// die scop
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture10);
			earth.display();
			Model = Save;
			//die Sone
			Model = glm::scale(Model, glm::vec3(1.0/10.0f, 1.0/10.0f, 1.0/10.0f));
			sendMVP();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture0);
			earth.display();
			// Zeichen alle Bahnen und bestimmen X und Z Punkten fuer Jeder Planet ,damit sie auf der Bahnen um die Sonne umdrehen werden in ellipsenförmig (oval form )
			DrawEllipse(0, 0, 60, 45, 100);
			rotateOnOrbit(1, 6.0, 4.5);
			DrawEllipse(0, 0, 85, 70, 100);
			rotateOnOrbit(2, 8.5, 7.0);
			DrawEllipse(0, 0, 110, 90, 100);
			rotateOnOrbit(3, 11.0, 9.0);
			DrawEllipse(0, 0, 140.0, 120, 100);
			rotateOnOrbit(4, 14.0, 12.0);
			DrawEllipse(0, 0, 185, 165, 100);
			rotateOnOrbit(5, 18.5, 16.5);
			DrawEllipse(0, 0, 240, 215, 100);
			rotateOnOrbit(6, 24.0, 21.5);
			DrawEllipse(0, 0, 290, 265, 100);
			rotateOnOrbit(7, 29.0, 26.5);
			DrawEllipse(0, 0, 325, 300, 100);
			rotateOnOrbit(8, 32.5, 30.0);
			sendMVP();
			Model = Save;
			// die erste  Mercury
			planetDrehung1(xForEarth1,yForEarth1, 0, plantetRotet1);
			glActiveTexture(GL_TEXTURE0);//
			glBindTexture(GL_TEXTURE_2D, Texture1);
			earth.display();
			Model = Save;
			// die zweite planet Venus
			planetDrehung1(xForEarth2, yForEarth2,1.5, plantetRotet2);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture2);
			earth.display();
			Model = Save;
			//3 die Erde
			planetDrehung1(xForEarth3, yForEarth3, 3.6, plantetRotet3);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture3);
			earth.display();
			sendMVP();
			drawHollowCircle(0.0, 0.0, 55.0f);
			sendMVP();
			Model = Save;
			// Der Mond	
			Model = glm::rotate(Model, plantetRotet3, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around the sun
			Model = glm::translate(Model, glm::vec3(xForEarth3, 0, yForEarth3));
			Model = glm::rotate(Model, MoonRotet, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around the Earth
			Model = glm::translate(Model, glm::vec3(1.5, 0.0, 0)); // translate from the center of the Earth 
			Model = glm::scale(Model, glm::vec3(1.0 / 85.0, 1.0 / 85.0, 1.0 / 85.0));
			sendMVP();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture9);
			earth.display();
			Model = Save;
			// 4 die Mars
			planetDrehung1(xForEarth4, yForEarth4, 1.4, plantetRotet4);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture4);
			earth.display();
			Model = Save;
			// die 5 Jupiter
			planetDrehung1(xForEarth5, yForEarth5, 27.0, plantetRotet5);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture5);
			earth.display();
			Model = Save;
			// die 6 Saturn
			planetDrehung1(xForEarth6, yForEarth6, 22.0, plantetRotet6);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture6);
			earth.display();
			drawHollowCircleRing(); 
			sendMVP();
			Model = Save;
			// die 7 Uranus
			planetDrehung1(xForEarth7, yForEarth7, 10.0, plantetRotet7);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture7);
			earth.display();
			Model = Save;
			// die 8 Nepton
			planetDrehung1(xForEarth8, yForEarth8, 9.0, plantetRotet8);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture8);
			earth.display();
			Model = Save;
		}
		else
		{
			glm::vec3 lightPos = glm::vec3(0.0, 0, 0);
			glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);
			sendMVP();
			Model = glm::scale(Model, glm::vec3(1.0 / 20.0f, 1.0 / 20.0f, 1.0 / 20.0f));

			sendMVP();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture0);
			earth.display();
			drawHollowCircle(0.0, 0, 86.0f);
			sendMVP();
			Model = Save;

			// die Erde
			planetDrehung(15.0f, 10.0f, 0.0f);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture3);
			earth.display();
			drawHollowCircle(0.0, 0.0, 150.0f);
			sendMVP();
			Model = Save;
			if (!moonfenster) {
				Model = glm::translate(Model, glm::vec3(15.0, 0.0, 0));
				Model = glm::rotate(Model, MoonRotet_finster, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around the Earth
				Model = glm::translate(Model, glm::vec3(-5.0, 0.0, 0.0)); // translate from the center of the Earth 
				Model = glm::scale(Model, glm::vec3(1.0 / 50.0, 1.0 / 50.0, 1.0 / 50.0));
			}
			else {
				Model = glm::translate(Model, glm::vec3(15.0, 0.0, 0));
				Model = glm::rotate(Model, MoonRotet_finster, glm::vec3(0.0f, -1.0f, 0.0f));// rotate around the Earth
				Model = glm::translate(Model, glm::vec3(5.0, 0.0, 0.0)); // translate from the center of the Earth 
				Model = glm::scale(Model, glm::vec3(1.0 / 50.0, 1.0 / 50.0, 1.0 / 50.0));
			}
			sendMVP();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture9);
			earth.display();
			Model = Save;
		
		}
		glm::vec4 lightPos = glm::vec4(0,0, 0,0.1);
		glUniform3f(glGetUniformLocation(programID, "LightPosition_worldspace"), lightPos.x, lightPos.y, lightPos.z);
		sendMVP();	
		// Swap buffers
		glfwSwapBuffers(window);
		// Poll for and process events 
        glfwPollEvents();
	}
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture0);
	glDeleteTextures(1, &Texture1);
	glDeleteTextures(1, &Texture2);
	glDeleteTextures(1, &Texture3);
	glDeleteTextures(1, &Texture4);
	glDeleteTextures(1, &Texture5);
	glDeleteTextures(1, &Texture6);
	glDeleteTextures(1, &Texture7);
	glDeleteTextures(1, &Texture8);
	glDeleteTextures(1, &Texture9);
	glDeleteTextures(1, &Texture10);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

