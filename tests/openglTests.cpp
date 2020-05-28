//
// Created by niubo on 5/27/2020.
//
#include "gtest/gtest.h"
#include <iostream>
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
#include "../BoMath/BoQuaternion.h"
#include "../BoMath/BoMatrix.h"
#include "../common/objloader.hpp"
#include "../common/shader.hpp"
#include "../common/texture.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../globalUtil.h"
#include <vector>
using namespace std;
GLFWwindow *window;

TEST(OpenGLTests, OpenGLTest1) {
    cout << "hello, I am in the OpenGLTests: OpenGLTests1 " << endl;
    ASSERT_EQ(1, 1);
}

TEST(OpenGLTests, OpenGLTest2) {
    ASSERT_EQ(1, 1);

//    //BoMatrixXf tm(4, 4);
//    //tm << 4.0f, 2.0f, 7.0f,0,
//    //	1.0f, 4.0f, 3.0f,0,
//    //	2.0f, 5.0f, 8.0f,0,
//    //	0,0,0,1;
//    //std::cout << "test Matrix:\n" << tm << std::endl;
//    //BoMatrixXf inv = tm.inverse();
//    //std::cout << "inv:\n" << inv << std::endl;
//
//    if (!glfwInit())return;
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        return;
//    }
//    glfwMakeContextCurrent(window);
//    if (glewInit() != GLEW_OK) {
//        std::cout << "Error" << std::endl;
//    }
//
//    //GLint nrAttributes;
//    //glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//    //std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
//
//    {
//        //////test quaternion/////////////////////////////////
//        BoQuaternionF qTotal;
//        float angle = 0.01;
//        //BoQuaternionF qRotate = BoQuaternionF::generateQuaternion(-1, 4, 0, angle);
//        BoQuaternionF qRotate = BoQuaternionF::generateQuaternion(0, 0, 1, angle);
//        //////////////////////////////////////////////////////
//
//
//        ///////test BoMatrix4f/////////////////////////////////
//        BoMatrix4f matTotal, matTotal1_2;
//        //BoMatrix4f matRotate = BoMatrix4f::rotate(0.001, 0, 0);
//        BoMatrix4f matRotate = BoMatrix4f::rotateY(0.005);
//        //////////////////////////////////////////////////////
//
//        unsigned int indices[] = {
//                0,1,2,
//                2,3,0
//        };
//
//        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//        GLCall(glEnable(GL_BLEND));
//        glEnable(GL_DEPTH_TEST);
//        // Accept fragment if it closer to the camera than the former one
//        glDepthFunc(GL_LESS);
//
//
//        glm::mat4 proj = glm::ortho(-2.0, 2.0, -1.5, 1.5, -1.0, 1.0);
//        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0, 0, 0));
//        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
//
//        glm::mat4 rotateXMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
//        glm::mat4 rotateYMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.005f / 3.14f * 180.0f), glm::vec3(0.f, 1.f, 0.f));
//        glm::mat4 rotateZMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
//        glm::mat4 rotateAll = rotateXMat * rotateYMat * rotateZMat;
//
//        glm::mat4 mvp = proj * rotateAll * view * model;
//
//        Shader shader("vertex.shader", "fragment.shader");
//        shader.Bind();
//        Shader shader1_2("vertex.shader", "fragment.shader");
//        shader1_2.Bind();
//
//        float r = 0.0f;
//        float increment = 0.01f;
//
//        Renderer renderer1_1;
//        Renderer renderer1_2;
//        Renderer renderer2_1;
//        Renderer renderer2_2;
//        float positions[12] = { 0.2f, 0.2f,0.1,
//                                0.8f, 0.2f,0.1,
//                                0.8f, 0.4f,0.1,
//                                0.2f, 0.4f,0.1 };
//        while (!glfwWindowShouldClose(window)) {
//
//            /*renderer1_1.Clear();
//            renderer1_2.Clear();*/
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            shader.Bind();
//            shader.SetUniform4f("u_Color", 1.0, 0.0f, 0.0f, 1.0f);
//            shader.SetUniformMat4f("u_MVP", mvp);
//            float positionsFinal[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
//            qTotal = qRotate * qTotal;
//            //BoMatrixXf m2 = qTotal.toMatrix()/*.inverse()*/ * v;
//            matTotal = matRotate * matTotal;
//            for (int i = 0; i < 4; i++) {
//                BoVector4f v;
//                v << positions[3 * i], positions[3 * i + 1], positions[3 * i + 2], 0;
//
//
//                BoVector4f v2 = matTotal * v;
//
//                positionsFinal[3 * i] = v[0]; //v2[0];
//                positionsFinal[3 * i + 1] = v[1]; //v2[1];
//                positionsFinal[3 * i + 2] = v[2]; //v2[2];
//            }
//            VertexArray va;
//            VertexBuffer vb(positionsFinal, 3 * 4 * sizeof(float));
//            VertexBufferLayout layout;
//            layout.Push<float>(3);//position
//            va.AddBuffer(vb, layout);
//            IndexBuffer ib(indices, 6);
//            renderer1_1.Draw(va, ib, shader);
//            shader1_2.Bind();
//            shader1_2.SetUniform4f("u_Color", 0.0, 1.0f, 0.0f, 1.0f);
//            shader1_2.SetUniformMat4f("u_MVP", mvp);
//            matTotal1_2 = matRotate * matTotal1_2;
//
//            //////////////////////////////////////////////////////////////////////////
//            //////////////////////////////////////////////////////////////////////////
//            // Read OBJ File
//            // Read our .obj file
//            GLuint VertexArrayID;
//            glGenVertexArrays(1, &VertexArrayID);
//            glBindVertexArray(VertexArrayID);
//
//            // Create and compile our GLSL program from the shaders
//            GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
//
//            // Get a handle for our "MVP" uniform
//            GLuint MatrixID = glGetUniformLocation(programID, "MVP");
//
//            // Load the texture
//            GLuint Texture = loadDDS("uvmap.DDS");
//
//            // Get a handle for our "myTextureSampler" uniform
//            GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
//
//            // Read our .obj file
//            std::vector<glm::vec3> vertices;
//            std::vector<glm::vec2> uvs;
//            std::vector<glm::vec3> normals; // Won't be used at the moment.
//            bool res = loadOBJ("cube.obj", vertices, uvs, normals);
//
//            GLuint vertexbuffer;
//            glGenBuffers(1, &vertexbuffer);
//            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
//
//            GLuint uvbuffer;
//            glGenBuffers(1, &uvbuffer);
//            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
//            //////////////////////////////////////////////////////////////////////////
//            //////////////////////////////////////////////////////////////////////////
//
//
//            for (int i = 0; i < 4; i++) {
//                BoVector4f v;
//                v << positions[3 * i], positions[3 * i + 1], positions[3 * i + 2] + 0.01, 0;
//                //BoMatrixXf m2 = qTotal.toMatrix()/*.inverse()*/ * v;
//
//                BoVector4f v2 = matTotal1_2 * v;
//                positionsFinal[3 * i] = v[0]; //v2[0];
//                positionsFinal[3 * i + 1] = v[1]; //v2[1];
//                positionsFinal[3 * i + 2] = v[2]; //v2[2];
//                std::cout << "z: " << std::to_string(v2[2]) << std::endl;
//            }
//            VertexArray va1_2;
//            VertexBuffer vb1_2(positionsFinal, 3 * 4 * sizeof(float));
//            VertexBufferLayout layout1_2;
//            layout1_2.Push<float>(3);//position
//            va1_2.AddBuffer(vb1_2, layout1_2);
//            IndexBuffer ib1_2(indices, 6);
//            renderer1_2.Draw(va1_2, ib1_2, shader1_2);
//
//            if (r > 1.0f) {
//                increment = -0.01f;
//            }
//            else if (r < 0.0f) {
//                increment = 0.01f;
//            }
//            r += increment;
//
//            glfwSwapBuffers(window);
//            glfwPollEvents();
//
//
//            /////////////////////////unbind everything
//            //GLCall(glBindVertexArray(0));
//            va.Unbind();
//            shader.Unbind();
//            vb.Unbind();
//            ib.Unbind();
//            /////////////////////////
//
//            mvp = rotateAll * mvp;
//        }
//    }
//    glfwTerminate();
}

TEST(OpenGLTests, OpenGLTest3) {

//    //BoMatrixXf tm(4, 4);
//    //tm << 4.0f, 2.0f, 7.0f,0,
//    //	1.0f, 4.0f, 3.0f,0,
//    //	2.0f, 5.0f, 8.0f,0,
//    //	0,0,0,1;
//    //std::cout << "test Matrix:\n" << tm << std::endl;
//    //BoMatrixXf inv = tm.inverse();
//    //std::cout << "inv:\n" << inv << std::endl;
//
//    if (!glfwInit())return;
//    glfwWindowHint(GLFW_SAMPLES, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    window = glfwCreateWindow(1024, 768, "Hello opengl", NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    if (glewInit() != GLEW_OK) {
//        std::cout << "Error" << std::endl;
//    }
//
//    //GLint nrAttributes;
//    //glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
//    //std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
//
//    {
//        //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//        //GLCall(glEnable(GL_BLEND));
//        //glEnable(GL_DEPTH_TEST);
//        //// Accept fragment if it closer to the camera than the former one
//        //glDepthFunc(GL_LESS);
//        // Enable depth test
//        glEnable(GL_DEPTH_TEST);
//        // Accept fragment if it closer to the camera than the former one
//        glDepthFunc(GL_LESS);
//        // Cull triangles which normal is not towards the camera
//        glEnable(GL_CULL_FACE);
//
//        //////////////////////////////////////////////////////////////////////////
//        //////////////////////////////////////////////////////////////////////////
//        // Read OBJ File
//        // Read our .obj file
//        GLuint VertexArrayID;
//        glGenVertexArrays(1, &VertexArrayID);
//        glBindVertexArray(VertexArrayID);
//
//        // Create and compile our GLSL program from the shaders
//        GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");
//
//        // Get a handle for our "MVP" uniform
//        GLuint MatrixID = glGetUniformLocation(programID, "MVP");
//
//        // Load the texture
//        GLuint Texture = loadDDS("uvmap.DDS");
//
//        // Get a handle for our "myTextureSampler" uniform
//        GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
//
//        // Read our .obj file
//        std::vector<glm::vec3> vertices;
//        std::vector<glm::vec2> uvs;
//        std::vector<glm::vec3> normals; // Won't be used at the moment.
//        bool res = loadOBJ("cube.obj", vertices, uvs, normals);
//
//        GLuint vertexbuffer;
//        glGenBuffers(1, &vertexbuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
//
//        GLuint uvbuffer;
//        glGenBuffers(1, &uvbuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
//        //////////////////////////////////////////////////////////////////////////
//        //////////////////////////////////////////////////////////////////////////
//
//
//        glm::mat4 ProjectionMatrix = glm::ortho(-2.0, 2.0, -1.50, 1.50, -2.0, 2.0);
//        //glm::mat4 ProjectionMatrix = glm::ortho(-1024.0, 1024.0, -768.0, 768.0, -1000.0, 1000.0);
//        glm::mat4 ViewMatrix = glm::mat4(1.0);
//        glm::mat4 ModelMatrix = glm::mat4(1.0);
//
//        glm::mat4 rotateXMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
//        glm::mat4 rotateYMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.005f / 3.14f * 180.0f), glm::vec3(0.f, 1.f, 0.f));
//        glm::mat4 rotateZMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
//        glm::mat4 rotateAll = rotateXMat * rotateYMat * rotateZMat;
//
//        glm::mat4 MVP = ProjectionMatrix * rotateAll * ViewMatrix * ModelMatrix;
//
//        while (!glfwWindowShouldClose(window)) {
//
//            MVP = glm::mat4();
//            /*renderer1_1.Clear();
//            renderer1_2.Clear();*/
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//            // Use our shader
//            glUseProgram(programID);
//
//            //MVP = rotateAll * MVP;
//
//
//            // Send our transformation to the currently bound shader,
//            // in the "MVP" uniform
//            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
//
//            // Bind our texture in Texture Unit 0
//            glActiveTexture(GL_TEXTURE0);
//            glBindTexture(GL_TEXTURE_2D, Texture);
//            // Set our "myTextureSampler" sampler to use Texture Unit 0
//            glUniform1i(TextureID, 0);
//
//            // 1rst attribute buffer : vertices
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//            glVertexAttribPointer(
//                    0,                  // attribute
//                    3,                  // size
//                    GL_FLOAT,           // type
//                    GL_FALSE,           // normalized?
//                    0,                  // stride
//                    (void*)0            // array buffer offset
//            );
//
//            // 2nd attribute buffer : UVs
//            glEnableVertexAttribArray(1);
//            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//            glVertexAttribPointer(
//                    1,                                // attribute
//                    2,                                // size
//                    GL_FLOAT,                         // type
//                    GL_FALSE,                         // normalized?
//                    0,                                // stride
//                    (void*)0                          // array buffer offset
//            );
//
//            // Draw the triangle !
//            glDrawArrays(GL_TRIANGLES, 0, vertices.size());
//            //glDisableVertexAttribArray(0);
//            //glDisableVertexAttribArray(1);
//            glfwSwapBuffers(window);
//            glfwPollEvents();
//
//
//        }
//    }
//    glfwTerminate();
}

TEST(OpenGLTests, OpenGLTest4) {

    ASSERT_EQ(1, 1);
    return;

    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "Tutorial 07 - Model Loading", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return;
    }

    // Set the mouse at the center of the screen
    glfwPollEvents();

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Load the texture
    GLuint Texture = loadDDS("uvmap.DDS");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

    // Read our .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    bool res = loadOBJ("cube.obj", vertices, uvs, normals);
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << glm::to_string(vertices[i]) << std::endl;
    }
    // Load it into a VBO


    // Compute the MVP matrix from keyboard and mouse input
    float aaa[16] = {
            1.810658, 0.0, 0.001596, 0.001593,
            0.0, 2.414214, 0.0, 0.0,
            0.002884, 0.0, -1.002001, -1.0,
            -0.014418, 0.0, 4.809804, 5.0
    };


    BoMatrix4f transform;
    transform << 1.810658, 0.0, 0.001596, 0.001593,
            0.0, 2.414214, 0.0, 0.0,
            0.002884, 0.0, -1.002001, -1.0,
            -0.014418, 0.0, 4.809804, 5.0;

    std::cout << "transform: \n" << transform << std::endl;


    glm::mat4 MVP(1.0);
    BoMatrix4f boRotateMat = BoMatrix4f::rotateZ(0.01);
    BoMatrix4f boTotal =  boRotateMat;
    memcpy(glm::value_ptr(MVP), aaa, sizeof(aaa));
    glm::mat4 rotateXMat = glm::rotate(glm::mat4(1.0f), glm::radians(0.05f), glm::vec3(0.f, 1.f, 0.f));
    do {
        boTotal = boTotal * boRotateMat;
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        //MVP = MVP * rotateXMat;

        std::vector<glm::vec3> vertices2;
        for (int i = 0; i < vertices.size(); i++)
        {
            BoVector4f v;
            v[0] = vertices[i].x;
            v[1] = vertices[i].y;
            v[2] = vertices[i].z;
            v = boTotal * v;
            glm::vec3 v2(v[0], v[1], v[2]);
            vertices2.push_back(v2);
        }


        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

        GLuint uvbuffer;
        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);


        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID, 0);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                1,                                // attribute
                2,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        glfwSwapBuffers(window);
        //glfwPollEvents();
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &uvbuffer);
    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0);

    // Cleanup VBO and shader
    /*glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);*/
    glDeleteProgram(programID);
    glDeleteTextures(1, &Texture);
    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return;
}