#include <scene/objects/model.h>
FACTORY_CLASS_REGISTER(scene::objects::TFactory, scene::objects::TModel, scene::objects::Model);

#include <memory>

#include "application.h"
#include "resources/manager.h"
#include "scene/scene.h"
#include "scene/node.h"

namespace scene::objects {

TModel::TModel(Node* parent):
Object(parent),
resourceModel_(std::static_pointer_cast<resources::Model>(parent->getScene()->getApplication()->getResourceManager()->getDefaultModel())),
resourceShader_(std::static_pointer_cast<resources::Shader>(parent->getScene()->getApplication()->getResourceManager()->getDefaultShader()))
{}

// IResource
void TModel::setLoaded() {
    resourceModel_->setLoaded();
    resourceShader_->setLoaded();
}

void TModel::setPreloaded() {
    resourceModel_->setPreloaded();
    resourceShader_->setPreloaded();
}

void TModel::setUnloaded() {
    resourceModel_->setUnloaded();
    resourceShader_->setUnloaded();
}

inline const std::filesystem::path &TModel::getPath() {
    return resourceModel_->getPath();
}

inline const common::IResource::LoadState &TModel::getLoadState() {
    return resourceModel_->getLoadState();
}

} // namespace scene::objects