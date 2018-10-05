#include "camera.h"

Camera::Camera(float x, float y, float z, float fov, int width, int height, float near, float far) {
	cameraPos = glm::vec3(x, y, z);
	float aspect = ((float)width) / ((float)height);
	std::cout << "Camera aspect set to: " << aspect << std::endl;
	projection = glm::perspective(glm::radians(fov), aspect, near, far);  
}

void Camera::addPos(float x, float y, float z) {
	cameraPos.x += x;
	cameraPos.y += y;
	cameraPos.z += z;
}