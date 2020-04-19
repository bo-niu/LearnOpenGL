//#define GLEW_STATIC //this has to be done when using glew's static lib, or define it in preprocessor definition
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

//static void ParseShader(const std::string& filepath) {
//	std::ifstream stream(filepath);
//
//}



//static unsigned int CompileShader(unsigned int type, const std::string& source) {
//	unsigned int id = glCreateShader(type);
//	const char* src = source.c_str();
//	glShaderSource(id, 1, &src, nullptr);
//	glCompileShader(id);
//
//	//TO DO: Error Handling
//	int result;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//	if (result == GL_FALSE) {
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		char* message = (char*)alloca(length * sizeof(char));
//		glGetShaderInfoLog(id, length, &length, message);
//		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " SHADER" << std::endl;
//		std::cout << message << std::endl;
//		glDeleteShader(id);
//		return 0;
//	}
//
//	return id;
//}
//
////my first shader
//static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//	unsigned int program = glCreateProgram();
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//	glLinkProgram(program);
//	glValidateProgram(program);
//
//	glDeleteProgram(vs);
//	glDeleteProgram(fs);
//
//	return program;
//
//}



int main() {
	GLFWwindow* window;
	if (!glfwInit())return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	//GLint nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	{
		//a vertex is not a position (vertex not only contain positon, but pos, normals, texture, ..., each of which is called a attribute)
		float positions[] = {
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f, 0.5f,
			 -0.5f, 0.5f
		};
		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		//unsigned int vao;
		//GLCall(glGenVertexArrays(1, &vao));
		//GLCall(glBindVertexArray(vao));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);


		IndexBuffer ib(indices, 6);


		//std::string vertexShader = filetobuf("vertex.shader");
		//std::string fragmentShader = filetobuf("fragment.shader");
		//unsigned int shader = CreateShader(vertexShader, fragmentShader);

		Shader shader("vertex.shader", "fragment.shader");
		//shader.Bind();
		float r = 0.0f;
		float increment = 0.01f;
		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);



		/////////////////////////unbind everything
		//GLCall(glBindVertexArray(0));
		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();
		/////////////////////////

		Renderer renderer;
		
		while (!glfwWindowShouldClose(window)) {

			renderer.Clear();
			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			renderer.Draw(va, ib, shader);


			if (r > 1.0f) {
				increment = -0.01f;
			}
			else if (r < 0.0f) {
				increment = 0.01f;
			}
			r += increment;

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}



