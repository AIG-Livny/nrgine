#include <gtest/gtest.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

int main(int argc, char* argv[]){
    glfwInit();
    auto window = glfwCreateWindow(10, 10, "TEST", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}