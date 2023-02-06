#pragma once

#include "common/factory.h"

namespace scene{
    class Node;
}

namespace scene::objects{

enum Type{
    Camera,
    Light,
    Model,
    Physical
};

class Common{
    private:
        Node* parent_;
    
    public:
        Common(Node* parent)
        : 
        parent_(parent)
        {}
        
        // Copy denied
        Common(const Common&)             = delete;
        Common& operator=(const Common&)  = delete;

        [[nodiscard]] inline Node* getParent(){return parent_;} 
};

using TFactory = common::Factory<Common, Node*>;

} // namespace scene::objects