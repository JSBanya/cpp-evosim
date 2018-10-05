#ifndef MODEL_H
#define MODEL_H

#include "glad/glad.h"
#include <iostream>

#define MODEL_LINES 2
#define MODEL_TRIANGLES 3

class Model {
public:
	Model(float points[], int numPoints, int modelType);
	void draw();
	void drawTriangles();
	void drawLines();
private:
	GLuint vao = 0;
	int size = 0;
	int modelType = 0;
};

#endif