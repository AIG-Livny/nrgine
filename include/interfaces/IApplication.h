#pragma once

#include <memory>

#include <GLFW/glfw3.h> 

namespace reactphysics3d{ class PhysicsCommon;}
namespace resources{ class Manager;}
namespace scene{ class Scene;}

class IApplication{
    public:
        virtual const std::unique_ptr<reactphysics3d::PhysicsCommon>& getPhysicsCommon  () = 0;
        virtual const std::unique_ptr<resources::Manager>& getResourceManager()            = 0;
        virtual const std::unique_ptr<scene::Scene>& getCurrentScene   ()                  = 0;
        virtual GLFWwindow* getGLFWWindow     ()                                     = 0;
        virtual void mouseMoveEvent (double xpos, double ypos)                             = 0;
        virtual void keyPressEvent  (int key, int scancode, int action, int mods)          = 0;
        virtual void run            ()                                                     = 0;
};

