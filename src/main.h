#ifndef MAIN_H
#define MAIN_H

#include "glad/glad.h"
#include "controls/keyboard.h"
#include "controls/camera.h"
#include "world/world.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

const float WORLD_WIDTH = 100.0f;
const float WORLD_HEIGHT = 100.0f;
const int WORLD_MAX_CELLS = 2000;

GLFWwindow* main_window;
Camera* main_camera;

int initOpenGL();
int initGLFW();
void scrollCallback(GLFWwindow* window, double xpos, double ypos);

#endif