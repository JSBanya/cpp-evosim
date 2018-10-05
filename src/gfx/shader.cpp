#include "shader.h"

Shader::Shader(const char* vertPath, const char* fragPath) {
	GLuint vertexShader = createShader(vertPath, GL_VERTEX_SHADER);
	if(vertexShader == 0) {
		std::cout << "Unable to create vertex shader " << vertPath << std::endl;
		return;
	}

	GLuint fragmentShader = createShader(fragPath, GL_FRAGMENT_SHADER);
	if(fragmentShader == 0) {
		std::cout << "Unable to create fragment shader " << fragPath << std::endl;
		return;
	}

	this->program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	std::cout << "Shader program linked, vertex: " << vertPath << " fragment:" << fragPath << std::endl;
}

void Shader::use() {
	glUseProgram(program);
}

void Shader::bindUniformMatrix4fv(const char* uniformName, glm::mat4 mat) {
	glUniformMatrix4fv(glGetUniformLocation(program, uniformName), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::bindUniform4fv(const char* uniformName, glm::vec4 vec) {
	glUniform4fv(glGetUniformLocation(program, uniformName), 1, glm::value_ptr(vec));
}

void Shader::bindUniform4f(const char* uniformName, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(program, uniformName), v1, v2, v3, v4);
}

// Create a shader from the given source
GLuint Shader::createShader(const char* path, GLenum shaderType) {
	GLuint handle = glCreateShader(shaderType);

	std::string source = readFile(path);
	if(source == "") {
		std::cout << "Failed to create shader: " << path << std::endl;
		return 0;
	}

	const GLchar* raw = (const GLchar*) source.c_str();
	glShaderSource(handle, 1, &raw, NULL);
	glCompileShader(handle);

	// Check for compile errors
	GLint isCompiled = 0;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(handle, 1024, NULL, infoLog);
		glDeleteShader(handle);

		std::cout << "Unable to compile " << path << ": " << std::endl;
		std::cout << infoLog << std::endl;

		return 0;
	}

	return handle;
}	

std::string Shader::readFile(const char* path) {
	std::ifstream ifs(path);
  	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	return content;
}