//
// Created by niubo on 5/27/2020.
//

#ifndef LEARNOPENGL_GLOBALUTIL_H
#define LEARNOPENGL_GLOBALUTIL_H
#include <cstring>
#include <string>
#include <vector>
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

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
                    x;\
                    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};



/*A simple function that will read a file into an allocated char pointer buffer*/
char* filetobuf(const char* file)
{
    FILE* fptr;
    long length;
    char* buf;
    std::string str(file);
    std::string realFile = str;//std::string("C:/delete/LearnOpenGL/") + str;
    fopen_s(&fptr, realFile.c_str(), "rb"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */{
        assert(fptr);
        return NULL;
    }

    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length + 1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */

    return buf; /* Return the buffer */
}



unsigned int CompileShader(unsigned int type, const std::string& source) {
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

int GetUniformLocation(const std::string& name, unsigned int shaderID)
{

    GLCall(int location = glGetUniformLocation(shaderID, name.c_str()));
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    return location;
}


#endif //LEARNOPENGL_GLOBALUTIL_H
