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
    auto& modelnode = currentScene_->getRoot()->createChildNode();
    auto& cameranode = currentScene_->getRoot()->createChildNode();
    auto& lightnode = currentScene_->getRoot()->createChildNode();
    modelnode.createModel("res/box.obj");
    for(int i = 0; i<10;i++){
        auto& model2node = currentScene_->getRoot()->createChildNode();
        model2node.createModel("res/box.obj");
        model2node.setPosition(5,-9+(i*2.1),-3);
        auto& mod2phys = model2node.createPhysical();
        mod2phys.getBody()->addCollider(physicsCommon_->createBoxShape(reactphysics3d::Vector3(1,1,1)) , reactphysics3d::Transform::identity() );
    }
    modelnode.createModel("res/backpack/backpack.obj");
    lightnode.createLight();
    lightnode.createModel("res/icosphere.obj");
    lightnode.setPosition(5,5,-3);
    cameranode.createCamera(); 
    cameranode.setPosition(3,0,10);
    auto& floor = currentScene_->getRoot()->createChildNode();
    floor.setPosition(0,-10,0);
    floor.setScale(100,1,100);
    floor.createModel("res/box.obj");
    auto& phys_floor = floor.createPhysical();
    phys_floor.getBody()->setType(reactphysics3d::BodyType::STATIC);
    reactphysics3d::BoxShape* BoxShape = getPhysicsCommon()->createBoxShape(reactphysics3d::Vector3(100,1,100)); 
    phys_floor.getBody()->addCollider(BoxShape , reactphysics3d::Transform::identity() );
    


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
    while (!glfwWindowShouldClose(window_)){
        float currentFrame = glfwGetTime();
        static float deltaTime;
        static float lastFrame;
        
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        int display_w, display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f,  0.55f, 0.60f,1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentScene_->UpdatePhysics(deltaTime);
        renderer_->Render(currentScene_);        
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
	    ImGui::NewFrame();

        static double last_time;
        double current_time = glfwGetTime();
        static float fps;
        if ((current_time - last_time) >= 1.0){
            fps = ImGui::GetIO().Framerate;
            last_time = current_time;
        }
    
        ImGui::SetNextWindowSize(ImVec2(300,100), ImGuiCond_FirstUseEver);
        ImGui::Begin("info");
        ImGui::Text("FPS: %f",fps);
        //auto campos = currentScene_->active_camera->parent.lock()->matrix.get_position();
        //ImGui::Text("Cam pos: X:%f Y:%f Z:%f",campos.x, campos.y, campos.z);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);  
		glfwPollEvents();
	}
    

	// Cleanup
    glfwDestroyWindow(window_);
    glfwTerminate();
}