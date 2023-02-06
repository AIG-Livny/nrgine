#include <scene/objects/model.h>
FACTORY_CLASS_REGISTER(scene::objects::TFactory, scene::objects::TModel, scene::objects::Model);


#include <memory>

#include "scene/node.h"

namespace scene::objects {

// IResource
void TModel::setLoaded() {
    resource_model_->setLoaded();
    resource_shader_->setLoaded();
}

void TModel::setPreloaded() {
    resource_model_->setPreloaded();
    resource_shader_->setPreloaded();
}

void TModel::setUnloaded() {
    resource_model_->setUnloaded();
    resource_shader_->setUnloaded();
}

inline const std::filesystem::path &TModel::getPath() {
    return resource_model_->getPath();
}

inline const common::IResource::LoadState &TModel::getLoadState() {
    return resource_model_->getLoadState();
}

// IMovable
        [[nodiscard]] inline       glm::vec3    TModel::getBackward      ()                             {return getParent()->getBackward();}
        [[nodiscard]] inline       glm::vec3    TModel::getForward       ()                             {return getParent()->getForward ();}
        [[nodiscard]] inline       glm::vec3    TModel::getLeft          ()                             {return getParent()->getLeft    ();}
        [[nodiscard]] inline       glm::vec3    TModel::getRight         ()                             {return getParent()->getRight   ();}
        [[nodiscard]] inline       glm::vec3    TModel::getDown          ()                             {return getParent()->getDown    ();}
        [[nodiscard]] inline       glm::vec3    TModel::getUp            ()                             {return getParent()->getUp      ();}
        [[nodiscard]] inline       glm::vec3    TModel::getPitch         ()                             {return getParent()->getPitch   ();}
        [[nodiscard]] inline       glm::vec3    TModel::getYaw           ()                             {return getParent()->getPitch   ();}
        [[nodiscard]] inline       glm::vec3    TModel::getRoll          ()                             {return getParent()->getRoll    ();}
        [[nodiscard]] inline const glm::vec3&   TModel::getScale         ()                             {return getParent()->getScale();}
        [[nodiscard]] inline const glm::quat&   TModel::getRotation      ()                             {return getParent()->getRotation();}
        [[nodiscard]] inline const glm::vec3&   TModel::getPosition      ()                             {return getParent()->getPosition();}
        [[nodiscard]] inline       glm::mat4&   TModel::getMatrix        ()                             {return getParent()->getMatrix();}
                      inline       void         TModel::setPosition      (const glm::vec3& pos)         {getParent()->setPosition(pos);}
                      inline       void         TModel::setPosition      (float x, float y, float z)    {getParent()->setPosition(x,y,z);}
                      inline       void         TModel::setScale         (const glm::vec3& scale)       {getParent()->setScale(scale);}
                      inline       void         TModel::setScale         (float x, float y, float z)    {getParent()->setScale(x,y,z);}
                      inline       void         TModel::setRotation      (const glm::quat& qrot)        {getParent()->setRotation(qrot);}
                      inline       void         TModel::setRotation      (float rx, float ry, float rz) {getParent()->setRotation(rx,ry,rz);}
                      inline       void         TModel::move             (glm::vec3 v)                  {getParent()->move(v);}
                      inline       void         TModel::rotate           (glm::quat qrot)               {getParent()->rotate(qrot);}    
                      inline       void         TModel::scale            (glm::vec3 v)                  {getParent()->scale(v);}

} // namespace scene::objects