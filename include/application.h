#pragma once

#include "common/forwards.h"

class Application{
    private:
        pu<reactphysics3d::PhysicsCommon>   physicsCommon_;
        pu<resources::Manager>              resourceManager_;
        pu<Renderer>                        renderer_;
        pu<scene::Scene>                    currentScene_;
        GLFWwindow*                         window_;

    public:
        Application();
        ~Application();
        
        [[nodiscard]] inline const auto& getPhysicsCommon  (){return physicsCommon_;}
        [[nodiscard]] inline const auto& getResourceManager(){return resourceManager_;}
        [[nodiscard]] inline const auto& getCurrentScene   (){return currentScene_;}
        [[nodiscard]] inline const auto& getGLFWWindow     (){return window_;}

        void mouseMoveEvent (double xpos, double ypos);
        void keyPressEvent  (int key, int scancode, int action, int mods);
        void setup          ();
        void run            ();
};