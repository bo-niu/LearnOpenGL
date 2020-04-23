//#define GLEW_STATIC //this has to be done when using glew's static lib, or define it in preprocessor definition
#define _USE_MATH_DEFINES
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
#include "Texture.h"

#include "BoMath/BoQuaternion.h"
#include "BoMath/BoMatrix.h"

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



//int main() {
//	GLFWwindow* window;
//	if (!glfwInit())return -1;
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	if (!window) {
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	if (glewInit() != GLEW_OK) {
//		std::cout << "Error" << std::endl;
//	}
//
//	//GLint nrAttributes;
//	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//	//std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
//
//	{
//		//a vertex is not a position (vertex not only contain positon, but pos, normals, texture, ..., each of which is called a attribute)
//		float positions[] = {
//			-0.5f, -0.5f,	0.0f, 0.0f,
//			0.5f, -0.5f,	1.0f, 0.0f,
//			0.5f, 0.5f,		1.0f, 1.0f,
//			 -0.5f, 0.5f,	0.0f, 1.0f
//		};
//		unsigned int indices[] = {
//			0,1,2,
//			2,3,0
//		};
//
//
//		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//		GLCall(glEnable(GL_BLEND));
//
//		//unsigned int vao;
//		//GLCall(glGenVertexArrays(1, &vao));
//		//GLCall(glBindVertexArray(vao));
//
//		VertexArray va;
//		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
//		VertexBufferLayout layout;
//		layout.Push<float>(2);//position
//		layout.Push<float>(2);//texture
//		va.AddBuffer(vb, layout);
//
//
//		IndexBuffer ib(indices, 6);
//
//
//		//std::string vertexShader = filetobuf("vertex.shader");
//		//std::string fragmentShader = filetobuf("fragment.shader");
//		//unsigned int shader = CreateShader(vertexShader, fragmentShader);
//
//		Shader shader("vertex.shader", "fragment.shader");
//		//shader.Bind();
//		float r = 0.0f;
//		float increment = 0.01f;
//		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//
//		//Texture texture("res/textures/logo.png");
//		//texture.Bind();
//		//shader.Bind();
//		//shader.SetUniform1i("u_Texture", 0);//0 corresponds to bind(0)
//
//
//
//		/////////////////////////unbind everything
//		//GLCall(glBindVertexArray(0));
//		va.Unbind();
//		shader.Unbind();
//		vb.Unbind();
//		ib.Unbind();
//		/////////////////////////
//
//		Renderer renderer;
//		
//		while (!glfwWindowShouldClose(window)) {
//
//			renderer.Clear();
//			shader.Bind();
//			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//			renderer.Draw(va, ib, shader);
//
//
//			if (r > 1.0f) {
//				increment = -0.01f;
//			}
//			else if (r < 0.0f) {
//				increment = 0.01f;
//			}
//			r += increment;
//
//			glfwSwapBuffers(window);
//			glfwPollEvents();
//		}
//	}
//	glfwTerminate();
//	return 0;
//}



int main() {


	BoMatrixXf tm(4, 4);
	tm << 4.0f, 2.0f, 7.0f,0,
		1.0f, 4.0f, 3.0f,0,
		2.0f, 5.0f, 8.0f,0,
		0,0,0,1;
	std::cout << "test Matrix:\n" << tm << std::endl;

	BoMatrixXf inv = tm.inverse();

	std::cout << "inv:\n" << inv << std::endl;




	GLFWwindow* window;
	if (!glfwInit())return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
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

		BoQuaternionF qTotal;
		float angle = 0.01;
		//BoQuaternionF qRotate = BoQuaternionF::generateQuaternion(-1, 4, 0, angle);
		BoQuaternionF qRotate = BoQuaternionF::generateQuaternion(0, 0, 1, angle);


		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};


		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));


		Shader shader("vertex.shader", "fragment.shader");
		shader.Bind();
		float r = 0.0f;
		float increment = 0.01f;

		

		Renderer renderer;
		float positions[8] = { 0.2f, 0.2f,0.5f, 0.2f,0.5f, 0.5f,0.2f, 0.5f };
		while (!glfwWindowShouldClose(window)) {

			renderer.Clear();
			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			float positionsFinal[8] = { 0,0,0,0,0,0,0,0 };
			qTotal = qRotate * qTotal;
			for (int i = 0; i < 4; i++) {
				BoMatrixXf m(4, 1);
				m << positions[2 * i], positions[2 * i + 1], 0, 0;
				BoMatrixXf m2 = qTotal.toMatrix()/*.inverse()*/ * m;
				positionsFinal[2 * i] = m2[0][0];
				positionsFinal[2 * i + 1] = m2[1][0];
			}



			VertexArray va;
			VertexBuffer vb(positionsFinal, 2 * 4 * sizeof(float));
			VertexBufferLayout layout;
			layout.Push<float>(2);//position
			va.AddBuffer(vb, layout);

			IndexBuffer ib(indices, 6);




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


			/////////////////////////unbind everything
		//GLCall(glBindVertexArray(0));
			va.Unbind();
			shader.Unbind();
			vb.Unbind();
			ib.Unbind();
			/////////////////////////


		}
	}
	glfwTerminate();
	return 0;
}
