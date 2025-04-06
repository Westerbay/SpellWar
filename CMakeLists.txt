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
    add_compile_options(-O2 -Wall)
endif()


# +------------------------------------------------------------------+
# | Librairies                                               |
# +------------------------------------------------------------------+
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/libs/GLFW")

if(WIN32)
    set(GLFW_LIB "${GLFW_DIR}/glfw3.lib")
elseif(UNIX)
    set(GLFW_LIB "${GLFW_DIR}/libglfw3.a")
endif()


# +------------------------------------------------------------------+
# | Source/Header Files                                          |
# +------------------------------------------------------------------+

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE FILE_SOURCES "${SRC_DIR}/*.c*")
file(GLOB_RECURSE FILE_HEADERS "${INCLUDE_DIR}/*.h*")

set(SOURCES ${FILE_SOURCES})
set(HEADERS ${FILE_HEADERS})

if(WIN32)
	add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})   
    #add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})   
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})   
endif()



# +------------------------------------------------------------------+
# | Link                                        |
# +------------------------------------------------------------------+
target_include_directories(${PROJECT_NAME} PRIVATE 
	${INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
	${GLFW_LIB}
	OpenGL::GL
)

