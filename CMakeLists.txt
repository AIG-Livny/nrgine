cmake_minimum_required(VERSION 3.25)
project (nrgine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(OUTPUT_FILE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})

#reactphysics3d
FILE(GLOB_RECURSE RP3D_SRC lib/reactphysics3d/src/*.cpp)
add_library(reactphysics3d ${RP3D_SRC})
target_include_directories(reactphysics3d PUBLIC lib/reactphysics3d/include)
#

#imgui
FILE(GLOB_RECURSE IMGUI_SRC lib/imgui/src/*.cpp)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC lib/imgui/include)
target_link_libraries(imgui glfw3)
#
FILE(GLOB_RECURSE SRC src/*.cpp)
add_executable (${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC include lib/reactphysics3d/include lib/imgui/include)

target_link_libraries(${PROJECT_NAME} glfw3 glew32 opengl32 reactphysics3d assimp imgui)

set_target_properties(${PROJECT_NAME} imgui reactphysics3d
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

#size checking
find_program(PYTHON "python")
IF(PYTHON)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND python size.py ${OUTPUT_FILE} -set)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND python size.py ${OUTPUT_FILE} -get)
ENDIF()
#

add_custom_target(release
   COMMAND mkdir -p release && cp -r res release/ && cp ${OUTPUT_FILE} release/
   DEPENDS ${OUTPUT_FILE} 
)
