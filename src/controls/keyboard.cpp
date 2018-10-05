#include "keyboard.h"

void processInput(GLFWwindow *window, Camera* camera) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    	camera->addPos(-1 * MOVEMENT_SPEED, 0.0f, 0.0f);
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    	camera->addPos(MOVEMENT_SPEED, 0.0f, 0.0f);
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    	camera->addPos(0.0f, MOVEMENT_SPEED, 0.0f);
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    	camera->addPos(0.0f, -1 * MOVEMENT_SPEED, 0.0f);
    }
}