#pragma once

namespace reactphysics3d{class PhysicsCommon;}
namespace resources     {class Manager;}
namespace scene         {class Scene;}
struct GLFWwindow;

class IApplication{
    public:
        virtual reactphysics3d::PhysicsCommon* getPhysicsCommon    () = 0;
        virtual resources::Manager*            getResourceManager  () = 0;
        virtual scene::Scene*                  getCurrentScene     () = 0;
        virtual GLFWwindow*                    getGLFWWindow       () = 0;
        
        virtual void mouseMoveEvent (double xpos, double ypos)                    = 0;
        virtual void keyPressEvent  (int key, int scancode, int action, int mods) = 0;
        virtual void run            ()                                            = 0;
};