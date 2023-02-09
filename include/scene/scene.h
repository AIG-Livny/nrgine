#pragma once

#include <vector>
#include <list>

#include "reactphysics3d/reactphysics3d.h"

#include "scene/node.h"
#include "scene/objects/object.h"

class Application;

namespace scene{

class Scene{
    friend Node;
    private:
        Application* application_;
        reactphysics3d::PhysicsWorld* physicsWorld_;
        std::unique_ptr<Node> rootNode_;
        std::vector<std::list<objects::Object*>> objects_;
    
    public:
        Scene(Application* app);
        ~Scene();
        
        Scene(const Scene&)               = delete;
        Scene& operator=(const Scene&)    = delete;
                
        [[nodiscard]] inline const auto& getRoot(){return rootNode_;}
        [[nodiscard]] inline const auto& getPhysicsCommon();
        [[nodiscard]] inline       auto* getPhysicsWorld(){ return physicsWorld_; }
        [[nodiscard]] inline       auto* getApplication(){ return application_; }
        [[nodiscard]] inline       auto& getObjects(objects::Type t){ return objects_[t]; }
        
        
        void UpdatePhysics(const float& delta);
};

} // END namespace scene