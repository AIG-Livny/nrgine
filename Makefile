OUT_FILE        = bin/NRgine
LINK_FLAGS 		= -g -O0
CFLAGS 			= -std=c++20 -fno-math-errno -g -O0

SUBPROJECTS += lib/reactphysics3d/bin/libreactphysics3d.a
SUBPROJECTS += lib/imgui/bin/libimgui.a

LIB_DIRS        += lib 
LIB_DIRS        += lib/imgui/bin
LIB_DIRS        += lib/reactphysics3d/bin
LIB_DIRS        += lib/glfw3/bin

INC_DIRS        += include
INC_DIRS        += lib/imgui/include
INC_DIRS        += lib/reactphysics3d/include
INC_DIRS        += lib/glfw3/include

LIBS            += GLEW32
LIBS            += GLU32
LIBS            += opengl32
LIBS            += glfw3
LIBS            += pthread
LIBS            += assimp
LIBS            += reactphysics3d
LIBS            += imgui
LIBS            += gtest
LIBS            += gmock

include common.mk