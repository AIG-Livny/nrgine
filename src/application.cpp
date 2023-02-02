#include "application.h"

#include <stdio.h>
#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "reactphysics3d/reactphysics3d.h"
#include "scene/scene.h"
#include "scene/node.h"
#include "resources/manager.h"
#include "resources/resource.h"
#include "resources/shader.h"
#include "renderer.h"

Application::~Application() = default;

#include "common/transform_matrix.h"
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp> 

Application::Application(){
    // Create window with graphics context
    window_ = glfwCreateWindow(1280, 720, "NAME VER", NULL, NULL);
    if (window_ == NULL){return ;}
    
    glfwMakeContextCurrent(window_);
    glewExperimental = GL_TRUE; 
    glewInit();
    glfwSwapInterval(1);    // Enable vsync
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);    
    
    
    
    physicsCommon_   = std::make_unique<reactphysics3d::PhysicsCommon>();
    resourceManager_ = std::make_unique<resources::Manager>();
    currentScene_    = std::make_unique<scene::Scene>(this);
      
    auto shader = resourceManager_->addShader("res/shaders");
    shader->setLoaded();
    auto modelnode = currentScene_->getRoot()->createChildNode();
    //auto cameranode = current_scene->root->CreateChildNode();
    //auto lightnode = scene->root->CreateChildNode();
    //auto lightnode = modelnode->CreateChildNode();
    //modelnode->CreateModel("res/box.obj");
    //for(int i = 0; i<10;i++){
    //    auto model2node = current_scene->root->CreateChildNode();
    //    model2node->CreateModel("res/box.obj");
    //    model2node->matrix.set_position(5,-9+(i*2.1),-3);
    //    auto mod2phys = model2node->CreatePhysicalObject();
    //    //mod2phys->body->addCollider (physics_common->createBoxShape(reactphysics3d::Vector3(1,1,1)) , reactphysics3d::Transform::identity() );
    //}
    //modelnode->CreateModel("res/backpack/backpack.obj");
    //lightnode->CreateLight();
    //lightnode->CreateModel("res/icosphere.obj");
    //lightnode->matrix.set_position(5,5,-3);
    //cameranode->CreateCamera(); 
    //cameranode->matrix.set_position(3,0,10);
    //auto floor = current_scene->root->CreateChildNode();
    //floor->SetPosition(0,-10,0);
    //floor->SetScale(100,1,100);
    //floor->CreateModel("res/box.obj");
    //auto phys_floor = floor->CreatePhysicalObject();
    //phys_floor->body->setType(reactphysics3d::BodyType::STATIC);
    //reactphysics3d::BoxShape* BoxShape = physics_common->createBoxShape(reactphysics3d::Vector3(100,1,100)); 
    //phys_floor->body->addCollider (BoxShape , reactphysics3d::Transform::identity() );
    


    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
}   

void Application::mouseMoveEvent(double xpos, double ypos){
    std::cout << "rr";    
}

void Application::keyPressEvent(int key, int scancode, int action, int mods){
    std::cout << "rr";    
}

void Application::run(){
    while(1){
        glfwPollEvents();
    }
}