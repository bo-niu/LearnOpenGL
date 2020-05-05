#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#pragma once
#include <stdio.h>
#include <unordered_map>
#include "glm/glm.hpp"


class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath_vertex;
	std::string m_FilePath_fragment;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filenameVertex, const std::string& filenameFragment);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniform1i(const std::string& name, int v0);
	void SetUniform4f(const std::string &name, float v0, float v1, float f2, float f3);
	void SetUniform1f(const std::string& name, float v0);
	void SetUniformMat4f(const std::string& name, const glm::mat4 &matrix);
private:
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	//bool CompileShader();
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	char* filetobuf(const char* file);
};

