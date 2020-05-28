#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "BoMath/BoQuaternion.h"
#include "BoMath/BoMatrix.h"
#include "common/objloader.hpp"
#include "common/shader.hpp"
#include "common/texture.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "globalUtil.h"
#include <vector>

extern GLFWwindow* window;

int main() {

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
	//GLint nrAttributes; glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes); std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	{
		//a vertex is not a position (vertex not only contain positon, but pos, normals, texture, ..., each of which is called a attribute)
		float positions[] = {
			-0.5f, -0.5f,	0.0f, 0.0f,
			0.5f, -0.5f,	1.0f, 0.0f,
			0.5f, 0.5f,		1.0f, 1.0f,
			 -0.5f, 0.5f,	0.0f, 1.0f
		};
		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		unsigned int vaID;
        GLCall(glGenVertexArrays(1, &vaID));
        unsigned int vbID;
        glGenBuffers(1, &vbID);//1. how many buffers. 2. bufferId returned.
        //1. the buffer we input is an array. 2. bufferId.
        //the binded buffer is the thing to draw. (state machine)
        glBindBuffer(GL_ARRAY_BUFFER, vbID);
        //specify the data
        glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), positions, GL_STATIC_DRAW);//1. buffer type. 2. size of buffer. 3. the real buffer. 4. usage hint

        std::vector<VertexBufferElement> layoutElements;
        unsigned int layoutStride = 0;
        layoutElements.push_back({ GL_FLOAT, 2, GL_FALSE });
        layoutStride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * 2;
        layoutElements.push_back({ GL_FLOAT, 2, GL_FALSE });
        layoutStride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * 2;

        GLCall(glBindVertexArray(vaID));
        glBindBuffer(GL_ARRAY_BUFFER, vbID);
        intptr_t offset = 0;
        for (unsigned int i = 0; i < layoutElements.size();i++) {
            const auto& element = layoutElements[i];

            GLCall(glEnableVertexAttribArray(i));
            //how many attributes a vertex has, how many times the function we have to call for each attribute.
            //GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));//the last two: 1. stride to next vertex. 2. offset to next attribute.
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layoutStride, (const void*)offset);
            ///important: glVertexAttribPointer link current bound buffer to current vao
            ///index buffer is a seperate thing.

            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);

        }

        unsigned int ibID;
        ASSERT(sizeof(unsigned int) == sizeof(GLuint));
        glGenBuffers(1, &ibID);//1. how many buffers. 2. bufferId returned.
        //1. the buffer we input is an array. 2. bufferId.
        //the binded buffer is the thing to draw. (state machine)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibID);
        //specify the data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLuint), indices, GL_STATIC_DRAW);//1. buffer type. 2. size of buffer. 3. the real buffer. 4. usage hint

        std::string vertexShaderFileName("vertex.shader"), fragmentShaderFileName("fragment.shader");
        std::string vertexShader = filetobuf(vertexShaderFileName.c_str());
        std::string fragmentShader = filetobuf(fragmentShaderFileName.c_str());

        unsigned int shaderID= glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(shaderID, vs);
        glAttachShader(shaderID, fs);
        glLinkProgram(shaderID);
        glValidateProgram(shaderID);

        glDeleteProgram(vs);
        glDeleteProgram(fs);

		float r = 0.0f;
		float increment = 0.01f;

		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		//Texture texture("res/textures/logo.png");
		//texture.Bind();
		//shader.Bind();
		//shader.SetUniform1i("u_Texture", 0);//0 corresponds to bind(0)

		/////////////////////////unbind everything
        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		/////////////////////////


		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		const char* glsl_version = "#version 130";
		ImGui_ImplOpenGL3_Init(glsl_version);
		// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		while (!glfwWindowShouldClose(window)) {

            glClear(GL_COLOR_BUFFER_BIT);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

            GLCall(glUseProgram(shaderID));
            GLCall(glUniform4f(GetUniformLocation("u_Color", shaderID), r, 0.3f, 0.8f, 1.0f));
            GLCall(glUseProgram(shaderID));
            GLCall(glBindVertexArray(vaID));
            glBindBuffer(GL_ARRAY_BUFFER, ibID);

            //glDrawArrays(GL_TRIANGLES, 0, 3);//1.draw mode 2. start index to draw 3. number of vertexes to draw
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if (r > 1.0f) {
				increment = -0.01f;
			}
			else if (r < 0.0f) {
				increment = 0.01f;
			}
			r += increment;

			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::SameLine();
			ImGui::Checkbox("Another Window", &show_another_window);
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwTerminate();
	return 0;
}



