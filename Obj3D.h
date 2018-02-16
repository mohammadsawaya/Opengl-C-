#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "objloader.hpp"

using namespace glm;

class Obj3D
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint VertexArrayIDTeapot;

	GLuint vertexbuffer;
	GLuint normalbuffer; // Hier alles analog für Normalen in location == 2
	GLuint uvbuffer; // Hier alles analog für Texturkoordinaten in location == 1 (2 floats u und v!)

public:
	Obj3D(const char* fn);//konstruktor
	void display();
	~Obj3D();//destruktor
};

