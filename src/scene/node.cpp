#include "scene/node.h"

#include <list>

namespace scene{
    Node& Node::createChildNode(){
        
    }
    
    Node::~Node() = default;
    Node::Node(Node* parent, Scene* scene)
            :
            parent_(parent),
            scene_(scene)
            {}
}