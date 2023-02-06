#pragma once

#include "scene/objects/common.h"

namespace scene{
    class Node;
} // namespace scene

namespace scene::objects{

class TLight : public Common{
    public:
	    TLight(Node* parent):
        Common(parent)
        {};
};

} // namespace scene::objects