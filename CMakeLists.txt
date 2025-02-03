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


# +------------------------------------------------------------------+
# | Librairies                                               |
# +------------------------------------------------------------------+
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


# +------------------------------------------------------------------+
# | Source Files                                          |
# +------------------------------------------------------------------+

file(GLOB LSYSTEM_SOURCES "src/LSystem/*.cpp")
file(GLOB WINDOWGL_SOURCES "src/WindowGL/*.cpp")
file(GLOB SPRITE_SOURCES "src/Sprite/*.cpp")
file(GLOB OBJECTGL_SOURCES "src/ObjectGL/*.cpp")
file(GLOB GLOBAL_SOURCES "src/*.cpp")

file(GLOB LSYSTEM_HEADERS "include/LSystem/*.hpp")
file(GLOB WINDOWGL_HEADERS "include/WindowGL/*.hpp")
file(GLOB SPRITE_HEADERS "include/Sprite/*.hpp")
file(GLOB OBJECTGL_HEADERS "include/ObjectGL/*.hpp")

set(SOURCES
    ${GLOBAL_SOURCES}
    ${LSYSTEM_SOURCES}
    ${WINDOWGL_SOURCES}
    ${SPRITE_SOURCES}
    ${OBJECTGL_SOURCES}
)

set(HEADERS
    ${LSYSTEM_HEADERS}
    ${WINDOWGL_HEADERS}
    ${SPRITE_HEADERS}
    ${OBJECTGL_HEADERS}
)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})   
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})   
endif()



# +------------------------------------------------------------------+
# | Link                                        |
# +------------------------------------------------------------------+
target_include_directories(${PROJECT_NAME} PRIVATE 
	include
	${GLM_DIR}
	${SDL3_DIR}/include
	${GLEW_DIR}/include
)

target_link_libraries(${PROJECT_NAME} 
	${SDL3_LIB}
	${GLEW_LIB}
	OpenGL::GL
)

