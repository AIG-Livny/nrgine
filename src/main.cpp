#include "application.h"

#include <stdio.h>
#include <GLFW/glfw3.h>

Application* app;

void glfw_error_callback(int error, const char* description){
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){  
    app->mouseMoveEvent(xpos,ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    app->keyPressEvent(key,scancode,action,mods);
}

int main(int argc, char* argv[]){
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()){
        return 0;
    }
    app = new Application();
    glfwSetCursorPosCallback(app->getGLFWWindow(), mouse_callback);
    glfwSetKeyCallback(app->getGLFWWindow(),key_callback);
    app->run();
    delete app;
    return 0;
}