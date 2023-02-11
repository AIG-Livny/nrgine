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
#include "scene/objects/object.h"
#include "scene/objects/model.h"
#include "scene/objects/camera.h"
#include "scene/objects/physical.h"
#include "resources/manager.h"
#include "resources/resource.h"
#include "resources/shader.h"
#include "renderer.h"

scene::Node* pcamnode;

Application::~Application() = default;

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
    currentScene_    = std::make_unique<scene::Scene>(static_cast<IApplication*>(this));
    
    
      
    auto resShader = resourceManager_->addShader("res/shaders");
    resShader->setLoaded();
    auto resModel = resourceManager_->addModel("res/box.obj");
    resModel->setLoaded();
    
    auto& modelnode = currentScene_->getRoot()->createChildNode();
    auto& cameranode = currentScene_->getRoot()->createChildNode();
    auto& lightnode = currentScene_->getRoot()->createChildNode();
    auto& model = modelnode.createObject(scene::objects::Model);
    model.setPosition(0,0,-20);
   
    
    for(int i = 0; i<10;i++){
        auto& model2node = currentScene_->getRoot()->createChildNode();
        model2node.createObject(scene::objects::Model);
        model2node.setPosition(5-(i*0.2),-9+(i*2.2),-3);
        auto& mod2phys = model2node.createObject(scene::objects::Physical);
        static_cast<scene::objects::TPhysical&>(mod2phys).getBody()->addCollider(physicsCommon_->createBoxShape(reactphysics3d::Vector3(1,1,1)) , reactphysics3d::Transform::identity() );
    }
    // static_cast<scene::objects::TModel&>(modelnode.createObject(scene::objects::Model)).setModel(resourceManager_->addModel("res/backpack/backpack.obj"));
    lightnode.createObject(scene::objects::Light);
    static_cast<scene::objects::TModel&>(lightnode.createObject(scene::objects::Model)).setModel(resourceManager_->addModel("res/icosphere.obj"));
    lightnode.setPosition(5,5,-3);
    cameranode.createObject(scene::objects::Camera); 
    cameranode.setPosition(3,0,10);
    pcamnode = &cameranode;
    auto& floor = currentScene_->getRoot()->createChildNode();
    floor.setPosition(0,-10,0);
    floor.setScale(100,1,100);
    floor.createObject(scene::objects::Model);
    auto& phys_floor = static_cast<scene::objects::TPhysical&>(floor.createObject(scene::objects::Physical));
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
    static glm::vec3 mouse_prev_pos;
    glm::vec3 mouse_current_pos = glm::vec3(ypos,xpos,0);
    glm::vec3 mouse_move = mouse_prev_pos - mouse_current_pos;
    mouse_prev_pos = mouse_current_pos;
    pcamnode->rotate(glm::quat(mouse_move*0.001f));
}

void Application::keyPressEvent(int key, int scancode, int action, int mods){
    if(action == GLFW_REPEAT){return;}
    //std::cout << "key:"<< key <<", scancode:" <<scancode<< ", action:" <<action<< ", mods:"<<mods << "\n";
    if((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)){
        glfwSetWindowShouldClose(window_, true);
    }
    float cameraSpeed = 2.5 * 0.1;//* deltaTime;
    if((key == GLFW_KEY_LEFT_SHIFT) && (action == GLFW_PRESS)){
        cameraSpeed *= 10;
    }
    //if(current_scene->active_camera cam == nullptr){
    //    return;
    //}
    if((key == GLFW_KEY_W) && (action == GLFW_PRESS)){
        pcamnode->move(pcamnode->getForward()*cameraSpeed);
    }
    
    if((key == GLFW_KEY_S) && (action == GLFW_PRESS)){
        pcamnode->move(pcamnode->getBackward()*cameraSpeed);
    } 
    if((key == GLFW_KEY_A) && (action == GLFW_PRESS)){
        pcamnode->move(pcamnode->getLeft()*cameraSpeed);
    }
    if((key == GLFW_KEY_D) && (action == GLFW_PRESS)){
        pcamnode->move(pcamnode->getRight()*cameraSpeed);
    }
    if((key == GLFW_KEY_SPACE) && (action == GLFW_PRESS)){
        pcamnode->move(pcamnode->getUp()*cameraSpeed);
    }
    if((key == GLFW_KEY_LEFT_CONTROL) && (action == GLFW_PRESS)){
        pcamnode->move(pcamnode->getDown()*cameraSpeed);
    }
    if((key == GLFW_KEY_Q) && (action == GLFW_PRESS)){
        pcamnode->rotate(glm::quat(pcamnode->getRoll() * cameraSpeed));
    }
    if((key == GLFW_KEY_E) && (action == GLFW_PRESS)){
        pcamnode->rotate(glm::quat(pcamnode->getRoll() * -cameraSpeed));
    }
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
        currentScene_->getObjects(scene::objects::Model).front()->rotate(glm::quat(glm::vec3(1,1,0)*0.01f));
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
        auto& campos = currentScene_->getObjects(scene::objects::Camera).front()->getPosition();
        auto camrot = glm::eulerAngles(currentScene_->getObjects(scene::objects::Camera).front()->getRotation());

        ImGui::Text("Cam pos: X:%f Y:%f Z:%f",campos.x, campos.y, campos.z);
        ImGui::Text("Cam rot: X:%f Y:%f Z:%f",camrot.x, camrot.y, camrot.z);
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