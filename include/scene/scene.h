#pragma once

#include "reactphysics3d/reactphysics3d.h"

#include "scene/node.h"

class Application;

namespace scene{

class Scene{
    private:
        Application* application_;
        reactphysics3d::PhysicsWorld* physicsWorld_;
        std::unique_ptr<Node> rootNode_;
    
    public:
        Scene(Application* app);
        ~Scene();
        
        Scene(const Scene&)               = delete;
        Scene& operator=(const Scene&)    = delete;
        
        [[nodiscard]] inline const auto& getRoot(){return rootNode_;}
        [[nodiscard]] inline const auto& getPhysicsCommon();
        [[nodiscard]] inline auto*       getPhysicsWorld(){ return physicsWorld_; }
        void UpdatePhysics(const float& delta);
};

} // END namespace scene