#pragma once

#include "scene/objects/common.h"
#include "reactphysics3d/reactphysics3d.h"

namespace scene{
    class Node;
}// namespace scene

namespace scene::objects{
    
class TPhysical : public Common{
    private:
        reactphysics3d::RigidBody* body_;
        
    public:
        TPhysical(Node* parent);
        ~TPhysical();
        
        [[nodiscard]] inline auto* getBody(){ return body_; }
};
    
}// namespace scene::objects