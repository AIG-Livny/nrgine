#pragma once

#include "scene/objects/object.h"
#include "reactphysics3d/reactphysics3d.h"

namespace scene{
    class Node;
}// namespace scene

namespace scene::objects{
    
class TPhysical : public Object{
    private:
        reactphysics3d::RigidBody* body_;
        
    public:
        TPhysical(Node* parent);
        ~TPhysical();
        
        [[nodiscard]] reactphysics3d::RigidBody*  getBody(){ return body_; }
        
        // Object
        [[nodiscard]] Type getType() const override {return Type::Physical;} 
};
    
}// namespace scene::objects