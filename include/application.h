#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include "interfaces/IApplication.h"
#include "reactphysics3d/reactphysics3d.h"
#include "resources/manager.h"
#include "scene/scene.h"
#include "renderer.h"

class Application : IApplication{
    private:
        std::unique_ptr<reactphysics3d::PhysicsCommon>   physicsCommon_;
        std::unique_ptr<resources::Manager>              resourceManager_;
        std::unique_ptr<Renderer>                        renderer_;
        std::unique_ptr<scene::Scene>                    currentScene_;
        GLFWwindow*                         window_;

    public:
        Application();
        ~Application();

        Application(const Application&)               = delete;
        Application& operator=(const Application&)    = delete;
        
        [[nodiscard]] inline const std::unique_ptr<reactphysics3d::PhysicsCommon>& getPhysicsCommon  (){return physicsCommon_;}
        [[nodiscard]] inline const std::unique_ptr<resources::Manager>& getResourceManager(){return resourceManager_;}
        [[nodiscard]] inline const std::unique_ptr<scene::Scene>& getCurrentScene   (){return currentScene_;}
        [[nodiscard]] inline GLFWwindow* getGLFWWindow     (){return window_;}

        void mouseMoveEvent (double xpos, double ypos);
        void keyPressEvent  (int key, int scancode, int action, int mods);
        void run            ();
};