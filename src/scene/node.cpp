#include "scene/node.h"

#include <list>

#include "scene/scene.h"
#include "scene/objects/model.h"
#include "scene/objects/physical.h"
#include "scene/objects/light.h"

namespace scene {

Node::Node(Node* parent, Scene* scene) :
    parent_(parent),
    scene_(scene) 
    {}

Node& Node::createChildNode() {
    childs_.push_back(std::make_unique<Node>(this, scene_));
    return *childs_.back();
}

objects::Object& Node::createObject(objects::Type t){
    assets_.push_back(objects::TFactory::Create(t, this));
    scene_->objects_[t].push_back(assets_.back().get());
    return *assets_.back();
}

} // namespace scene