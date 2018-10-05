#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>
#include "camera.h"

const float MOVEMENT_SPEED = 0.2f;

void processInput(GLFWwindow *window, Camera* camera);

#endif