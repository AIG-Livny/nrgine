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
                
        [[nodiscard]] inline reactphysics3d::PhysicsCommon* getPhysicsCommon   (){return getApplication()->getPhysicsCommon();}
        [[nodiscard]] inline reactphysics3d::PhysicsWorld*  getPhysicsWorld    (){return physicsWorld_;}
        [[nodiscard]] inline Node*                          getRoot            (){return rootNode_.get();}
        [[nodiscard]] inline IApplication*                  getApplication     (){return application_;}
        [[nodiscard]] inline std::list<objects::Object*>&   getObjects(objects::Type t){return objects_[t];}
        
        
        void UpdatePhysics(const float& delta);
};

} // namespace scene