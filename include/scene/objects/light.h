#pragma once

#include "scene/objects/object.h"

namespace scene{
    class Node;
} // namespace scene

namespace scene::objects{

class TLight : public Object{
    public:
	    TLight(Node* parent):
        Object(parent)
        {};
        
        // Object
        [[nodiscard]] Type getType() const override {return Type::Light;}
};

} // namespace scene::objects