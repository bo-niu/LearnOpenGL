//#define GLEW_STATIC //this has to be done when using glew's static lib, or define it in preprocessor definition
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
					x;\
					ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError() {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]: " << error << std::endl;
	}
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]: " << error << std::endl
			<< function << std::endl << file << ": " << line << std::endl;
		return false;
	}
	return true;
}

//static void ParseShader(const std::string& filepath) {
//	std::ifstream stream(filepath);
//
//}

/*A simple function that will read a file into an allocated char pointer buffer*/
char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fopen_s(&fptr, file, "rb"); /* Open file for reading */
	if (!fptr) /* Return NULL on failure */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	length = ftell(fptr); /* Find out how many bytes into the file we are */
	buf = (char*)malloc(length + 1); /* Allocate a buffer for the entire length of the file and a null terminator */
	fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	fclose(fptr); /* Close the file */
	buf[length] = 0; /* Null terminator */

	return buf; /* Return the buffer */
}

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

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	unsigned int buffer;
	glGenBuffers(1, &buffer);//1. how many buffers. 2. bufferId returned.

	//1. the buffer we input is an array. 2. bufferId.
	//the binded buffer is the thing to draw. (state machine)
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	//specify the data
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);//1. buffer type. 2. size of buffer. 3. the real buffer. 4. usage hint

	GLCall(glEnableVertexAttribArray(0));

	//how many attributes a vertex has, how many times the function we have to call for each attribute.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);//the last two: 1. stride to next vertex. 2. offset to next attribute.
	///important: glVertexAttribPointer link current bound buffer to current vao
	///index buffer is a seperate thing.

	unsigned int ibo;//index buffer object
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	//std::string vertexShader =
	//	"#version 330 core\n"
	//	"\n"
	//	"layout(location  = 0) in vec4 position;\n"//location = 0 => index of our attribute(match with glVertexAttribPointer)
	//											   //use vec4 instead of vec2 for convenience(just use vec4 all time)
	//	"void main()\n"
	//	"{\n"
	//	"gl_Position = position;\n"
	//	"\n"
	//	"\n"
	//	"}\n";
	std::string vertexShader = filetobuf("vertex.shader");


	//std::string fragmentShader =
	//	"#version 330 core\n"
	//	"\n"
	//	"layout(location  = 0) out vec4 color;\n"
	//	"void main()\n"
	//	"{\n"
	//	"	color = vec4(1.0, 0.0, 0.0, 1.0);\n"
	//	"\n"
	//	"\n"
	//	"}\n";
	std::string fragmentShader = filetobuf("fragment.shader");


	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);
	



	/////////////////////////unbind everything
	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	/////////////////////////


	float r = 0.0f;
	float increment = 0.01f;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);


		GLCall(glUseProgram(shader));
		GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
		GLCall(glBindVertexArray(vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

		//glDrawArrays(GL_TRIANGLES, 0, 3);//1.draw mode 2. start index to draw 3. number of vertexes to draw
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f) {
			increment = -0.01f;
		}
		else if (r < 0.0f){
			increment = 0.01f;
		}
		r += increment;

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}



