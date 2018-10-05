#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Shader {
public:
	Shader(const char* vertPath, const char* fragPath);
	void use();
	void bindUniformMatrix4fv(const char* uniformName, glm::mat4 mat);
	void bindUniform4fv(const char* uniformName, glm::vec4 vec);
	void bindUniform4f(const char* uniformName, float v1, float v2, float v3, float v4);
private:
	GLuint createShader(const char* path, GLenum shaderType);
	std::string readFile(const char* path);
private:
	GLuint program;
};

#endif