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
        
        [[nodiscard]] inline reactphysics3d::PhysicsCommon* getPhysicsCommon  () const override {return physicsCommon_.get();}
        [[nodiscard]] inline resources::Manager*            getResourceManager() const override {return resourceManager_.get();}
        [[nodiscard]] inline scene::Scene*                  getCurrentScene   () const override {return currentScene_.get();}
        [[nodiscard]] inline GLFWwindow*                    getGLFWWindow     () const override {return window_;}

        void mouseMoveEvent (double xpos, double ypos)                      override;
        void keyPressEvent  (int key, int scancode, int action, int mods)   override;
        void run            ()                                              override;
};