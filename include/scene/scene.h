#pragma once

#include <vector>
#include <list>

#include "reactphysics3d/reactphysics3d.h"

#include "interfaces/IApplication.h"
#include "scene/node.h"
#include "scene/objects/object.h"

namespace scene{

class Scene{
    
    friend Node;
    
    private:
        IApplication*                               application_;
        reactphysics3d::PhysicsWorld*               physicsWorld_;
        std::unique_ptr<Node>                       rootNode_;
        std::vector<std::list<objects::Object*>>    objects_;
    
    public:
        Scene(IApplication* app);
        ~Scene();
        
        // Deny copy
        Scene(const Scene&)               = delete;
        Scene& operator=(const Scene&)    = delete;
                
        [[nodiscard]] reactphysics3d::PhysicsCommon* getPhysicsCommon ()         const {return getApplication()->getPhysicsCommon();}
        [[nodiscard]] reactphysics3d::PhysicsWorld*  getPhysicsWorld  ()         const {return physicsWorld_;}
        [[nodiscard]] Node*                          getRoot          ()         const {return rootNode_.get();}
        [[nodiscard]] IApplication*                  getApplication   ()         const {return application_;}
        [[nodiscard]] std::list<objects::Object*>&   getObjects(objects::Type t)       {return objects_[t];}
        
        
        void updatePhysics(float delta);
};

} // namespace scene