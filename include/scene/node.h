#pragma once

#include "common/forwards.h"

#include <list>

namespace scene{
    class Node{
        private:
            Node* parent_;
            Scene* scene_;
            std::list<pu<char>> childs_;
            //std::list<ps<resources::Resource>> assets;
            
        public:
            Node(Node* parent, Scene* scene);
            
            ~Node();
            
            Node& createChildNode();
    };
}