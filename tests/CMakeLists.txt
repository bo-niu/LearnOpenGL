add_executable(OpenGLTest openglTests.cpp
        ../common/controls.cpp ../common/controls.hpp ../common/vboindexer.cpp ../common/vboindexer.hpp
        ../common/objloader.cpp ../common/objloader.hpp ../common/quaternion_utils.cpp ../common/quaternion_utils.hpp
        ../common/shader.cpp ../common/shader.hpp ../common/tangentspace.cpp ../common/tangentspace.hpp
        ../common/text2D.cpp ../common/text2D.hpp ../common/texture.cpp ../common/texture.hpp)
target_link_libraries(OpenGLTest gtest_main)
add_test(NAME OpenGLTest COMMAND OpenGLTest)


if (WIN32)
    target_compile_definitions(OpenGLTest PUBLIC GLEW_STATIC )
    target_include_directories(OpenGLTest PUBLIC "../Dependencies/glfw-3.3.2.bin.WIN64/include")
    target_link_directories(OpenGLTest PUBLIC "../Dependencies/glfw-3.3.2.bin.WIN64/lib-vc2019" )
    target_include_directories(OpenGLTest PUBLIC "../Dependencies")
    target_include_directories(OpenGLTest PUBLIC "../Dependencies/glew-2.1.0/include")
    target_link_directories(OpenGLTest PUBLIC "../Dependencies/glew-2.1.0/lib/Release/x64")
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

if (WIN32)
    target_link_libraries (OpenGLTest
            ${OPENGL_LIBRARIES} glfw3 glew32s glu32 opengl32)
endif (WIN32)

if (UNIX)
    target_link_libraries (sample
            ${OPENGL_LIBRARIES}
            ${GLFW3_LIBRARY}
            ${GLEW_LIBRARY}
            Xxf86vm pthread Xrandr Xinerama Xi Xcursor)
endif (UNIX)