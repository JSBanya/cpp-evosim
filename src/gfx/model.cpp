#include "model.h"

Model::Model(float points[], int numPoints, int modelType) {
	this->size = numPoints;
	this->modelType = modelType;
	GLuint vbo = 0;

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numPoints * sizeof(float), points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, modelType, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::draw() {
	glBindVertexArray(vao);

	if(modelType == MODEL_LINES) {
		glDrawArrays(GL_LINES, 0, size/2);
	} else if(modelType == MODEL_TRIANGLES) {
		glDrawArrays(GL_TRIANGLES, 0, size/3);
	}
}

void Model::drawTriangles() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size/3);
}

void Model::drawLines() {
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, size/2);
}
