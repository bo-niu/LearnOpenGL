#include"Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

void GLCheckError() {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]: " << error << std::endl;
	}
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]: " << error << std::endl
			<< function << std::endl << file << ": " << line << std::endl;
		return false;
	}
	return true;
}



Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	//glDrawArrays(GL_TRIANGLES, 0, 3);//1.draw mode 2. start index to draw 3. number of vertexes to draw
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
