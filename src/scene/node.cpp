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
    return *(childs_.end()->get());
}

objects::Model& Node::createModel(std::string path) {
    assets_.push_back(std::make_unique<objects::Model>(this, path));
    return *static_cast<objects::Model*>(assets_.end()->get());
}

objects::Physical& Node::createPhysical() {
    assets_.push_back(std::make_unique<objects::Physical>(this));
    return *static_cast<objects::Physical*>(assets_.end()->get());
}

objects::Light& Node::createLight() {
    assets_.push_back(std::make_unique<objects::Light>(this));
    return *static_cast<objects::Light*>(assets_.end()->get());
}

objects::Camera& Node::createCamera() {
    assets_.push_back(std::make_unique<objects::Camera>(this));
    return *static_cast<objects::Camera*>(assets_.end()->get());
}

} // namespace scene