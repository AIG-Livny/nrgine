#pragma once

#include "scene/objects/basic.h"

namespace scene{
    class Node;
} // namespace scene

namespace scene::objects{

class Light : public Basic{
    public:
	    Light(Node* parent):
        Basic(parent)
        {};
};

} // namespace scene::objects