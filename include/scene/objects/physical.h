#pragma once

#include "scene/objects/basic.h"
#include "reactphysics3d/reactphysics3d.h"

namespace scene{
    class Node;
}// namespace scene

namespace scene::objects{
    
class Physical : public Basic{
    private:
        reactphysics3d::RigidBody* body_;
        
    public:
        Physical(Node* parent);
        
        [[nodiscard]] inline auto* getBody(){ return body_; }
};
    
}// namespace scene::objects