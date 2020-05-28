cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)
#file(GLOB SOURCES
#        *.h
#        *.cpp
#)
#message("now we have: ")
#message(${SOURCES})
#add_subdirectory(common)

#add_executable(LearnOpenGL IndexBuffer.cpp IndexBuffer.h Renderer.cpp Renderer.h Shader.cpp Shader.h
#        Source.cpp stb_image.cpp stb_image.h Texture.cpp Texture.h VertexArray.cpp VertexArray.h VertexBuffer.cpp
#        VertexBuffer.h VertexBufferLayout.cpp VertexBufferLayout.h)

add_executable(LearnOpenGL main.cpp stb_image.cpp stb_image.h globalUtil.h
        common/controls.cpp common/controls.hpp common/vboindexer.cpp common/vboindexer.hpp
        common/objloader.cpp common/objloader.hpp common/quaternion_utils.cpp common/quaternion_utils.hpp
        common/shader.cpp common/shader.hpp common/tangentspace.cpp common/tangentspace.hpp
        common/text2D.cpp common/text2D.hpp common/texture.cpp common/texture.hpp
        imgui/imconfig.h imgui/imgui.cpp imgui/imgui.h imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_impl_glfw.cpp
        imgui/imgui_impl_glfw.h imgui/imgui_impl_opengl3.cpp imgui/imgui_impl_opengl3.h imgui/imgui_internal.h
        imgui/imgui_widgets.cpp imgui/imstb_rectpack.h imgui/imstb_textedit.h imgui/imstb_truetype.h
        globalGLFWwindow.cpp)

if (NOT WIN32)
    set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
    set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)
    find_package (PkgConfig REQUIRED)
endif (NOT WIN32)


find_package (OpenGL REQUIRED)
if (WIN32)
    target_compile_definitions(LearnOpenGL PUBLIC GLEW_STATIC )
    target_include_directories(LearnOpenGL PUBLIC "Dependencies/glfw-3.3.2.bin.WIN64/include")
    target_link_directories(LearnOpenGL PUBLIC "Dependencies/glfw-3.3.2.bin.WIN64/lib-vc2019" )
    target_include_directories(LearnOpenGL PUBLIC Dependencies)
    target_include_directories(LearnOpenGL PUBLIC "Dependencies/glew-2.1.0/include")
    #target_link_directories(LearnOpenGL PUBLIC "Dependencies/glew-2.1.0/build/cmake/lib")
    target_link_directories(LearnOpenGL PUBLIC "Dependencies/glew-2.1.0/lib/Release/x64")
else (WIN32)
    find_package (glfw3 REQUIRED)
    find_package (GLM REQUIRED)
    find_package (GLEW REQUIRED STATIC)
endif (WIN32)
if (APPLE)
    include_directories(/usr/local/include)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVID_LIBRARY CoreVideo REQUIRED)
endif (APPLE)

#message("GLFW3_LIBRARY: ")
#message("${GLFW3_LIBRARY}")
#message("OPENGL_LIBRARIES: ")
#message("${OPENGL_LIBRARIES}")
#message("GLEW_LIBRARY: ")
#message("${GLEW_LIBRARY}")
#message("COCOA_LIBRARY: ")
#message("${COCOA_LIBRARY}")
#message("COREVID_LIBRARY: ")
#message("${COREVID_LIBRARY}")
#message("IOKIT_LIBRARY: ")
#message("${IOKIT_LIBRARY}")

if (WIN32)
    target_link_libraries (LearnOpenGL
            ${OPENGL_LIBRARIES} glfw3 glew32s glu32 opengl32)
    set_target_properties(LearnOpenGL PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_BUILD_DIR}/Debug)
    set_property(TARGET LearnOpenGL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "C:/delete/LearnOpenGL")
    message("my VS_DEBUGGER_WORKING_DIRECTORY: ${VS_DEBUGGER_WORKING_DIRECTORY}")
    message("my CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
    
endif (WIN32)

if (UNIX)
    target_link_libraries (sample
            ${OPENGL_LIBRARIES}
            ${GLFW3_LIBRARY}
            ${GLEW_LIBRARY}
            Xxf86vm pthread Xrandr Xinerama Xi Xcursor)
endif (UNIX)


INCLUDE(gtest.cmake)

add_subdirectory(tests)