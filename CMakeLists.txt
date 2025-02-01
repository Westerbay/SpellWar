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
add_definitions(-Wall -Wextra -O2)



set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)



set(SDL2_DIR "${CMAKE_SOURCE_DIR}/libs/SDL2")
set(GLEW_DIR "${CMAKE_SOURCE_DIR}/libs/glew")

if(WIN32)
    set(SDL2_LIB "${SDL2_DIR}/lib/SDL2.lib")
    set(GLEW_LIB "${GLEW_DIR}/lib/libGLEW.lib")
    set(SDL2MAIN_LIB "${SDL2_DIR}/lib/SDL2main.lib")
elseif(UNIX)
    set(SDL2_LIB "${SDL2_DIR}/lib/libSDL2.a")
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
	${lib/glm} 
	${SDL2_DIR}/include
	${GLEW_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
	${SDL2_LIB}
	${GLEW_LIB}
	OpenGL::GL
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ${SDL2MAIN_LIB})
endif()

