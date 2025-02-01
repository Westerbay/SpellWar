# +------------------------------------------------------------------+
# |  Projects Settings                                               |
# +------------------------------------------------------------------+
cmake_minimum_required(VERSION 3.10)
project(SpellWar)


# +------------------------------------------------------------------+
# |  Compilation flags                                               |
# +------------------------------------------------------------------+
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

if (MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /W4 /RTC-") 
else()
    add_compile_options(-O2 -Wall -Wextra)
endif()



set(SDL3_DIR "${CMAKE_SOURCE_DIR}/libs/SDL3")
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/libs/glew")
set(GLM_DIR "${CMAKE_SOURCE_DIR}/libs/glm")

if(WIN32)
    set(SDL3_LIB "${SDL3_DIR}/lib/SDL3.lib")
    set(GLEW_LIB "${GLEW_DIR}/lib/glew32.lib")
elseif(UNIX)
    set(SDL3_LIB "${SDL3_DIR}/lib/libSDL3.a")
    set(GLEW_LIB "${GLEW_DIR}/lib/libGLEW.a")
endif()

set(SOURCES
    src/Main.cpp
    src/LSystem/LSystem.cpp
    src/LSystem/StochasticRules.cpp
    src/LSystem/Interpreter.cpp
    src/Window/MainFrame.cpp
)

set(HEADERS
    include/LSystem/LSystem.hpp
    include/LSystem/StochasticRules.hpp
    include/LSystem/Interpreter.hpp
    include/LSystem/Rules.hpp
    include/Window/MainFrame.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})   

target_include_directories(${PROJECT_NAME} PRIVATE 
	include/Window 
	include/LSystem 
	${GLM_DIR}
	${SDL3_DIR}/include
	${GLEW_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
	${SDL3_LIB}
	${GLEW_LIB}
	OpenGL::GL
)

