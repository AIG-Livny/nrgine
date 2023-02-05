#pragma once

namespace scene{
    class Node;
}

namespace scene::objects{

class Basic{
    private:
        Node* parent_;
    
    public:
        Basic(Node* parent)
        : 
        parent_(parent)
        {}
        
        Basic(const Basic&)             = delete;
        Basic& operator=(const Basic&)  = delete;

        [[nodiscard]] inline Node* getParent(){return parent_;} 
};

} // END namespace scene::objects