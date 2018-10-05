#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Camera {
public:
	Camera(float x, float y, float z, float fov, int width, int height, float near, float far);
	void addPos(float x, float y, float z);
	glm::vec3 getPos() { return cameraPos; };
	glm::mat4 getProjection() { return projection; };
	glm::mat4 getView() { return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); };
private:
	const glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
	glm::vec3 cameraPos;
	glm::mat4 projection;
};

#endif