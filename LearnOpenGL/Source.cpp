//#define GLEW_STATIC //this has to be done when using glew's static lib, or define it in preprocessor definition
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//TO DO: Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << " SHADER" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

//my first shader
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteProgram(vs);
	glDeleteProgram(fs);

	return program;

}



int main() {
	GLFWwindow* window;
	if (!glfwInit())return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}

	//a vertex is not a position (vertex not only contain positon, but pos, normals, texture, ..., each of which is called a attribute)
	float positions[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		 0.5f, -0.5f
	};
	unsigned int buffer;
	glGenBuffers(1, &buffer);//1. how many buffers. 2. bufferId returned.

	//1. the buffer we input is an array. 2. bufferId.
	//the binded buffer is the thing to draw. (state machine)
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	//specify the data
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);//1. buffer type. 2. size of buffer. 3. the real buffer. 4. usage hint

	glEnableVertexAttribArray(0);

	//how many attributes a vertex has, how many times the function we have to call for each attribute.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//the last two: 1. stride to next vertex. 2. offset to next attribute.


	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location  = 0) in vec4 position;\n"//location = 0 => index of our attribute(match with glVertexAttribPointer)
												   //use vec4 instead of vec2 for convenience(just use vec4 all time)
		"void main()\n"
		"{\n"
		"gl_Position = position;\n"
		"\n"
		"\n"
		"}\n";


	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location  = 0) out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"\n"
		"\n"
		"}\n";


	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);



	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);//1.draw mode 2. start index to draw 3. number of vertexes to draw

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}