#include <scene/objects/model.h>

#include <memory>

#include "scene/node.h"

namespace scene::objects {

// IResource
void Model::setLoaded() {
    resource_model_->setLoaded();
    resource_shader_->setLoaded();
}

void Model::setPreloaded() {
    resource_model_->setPreloaded();
    resource_shader_->setPreloaded();
}

void Model::setUnloaded() {
    resource_model_->setUnloaded();
    resource_shader_->setUnloaded();
}

inline const std::filesystem::path &Model::getPath() {
    return resource_model_->getPath();
}

inline const common::IResource::LoadState &Model::getLoadState() {
    return resource_model_->getLoadState();
}

// IMovable
        [[nodiscard]] inline       glm::vec3    Model::getBackward      ()                             {return getParent()->getBackward();}
        [[nodiscard]] inline       glm::vec3    Model::getForward       ()                             {return getParent()->getForward ();}
        [[nodiscard]] inline       glm::vec3    Model::getLeft          ()                             {return getParent()->getLeft    ();}
        [[nodiscard]] inline       glm::vec3    Model::getRight         ()                             {return getParent()->getRight   ();}
        [[nodiscard]] inline       glm::vec3    Model::getDown          ()                             {return getParent()->getDown    ();}
        [[nodiscard]] inline       glm::vec3    Model::getUp            ()                             {return getParent()->getUp      ();}
        [[nodiscard]] inline       glm::vec3    Model::getPitch         ()                             {return getParent()->getPitch   ();}
        [[nodiscard]] inline       glm::vec3    Model::getYaw           ()                             {return getParent()->getPitch   ();}
        [[nodiscard]] inline       glm::vec3    Model::getRoll          ()                             {return getParent()->getRoll    ();}
        [[nodiscard]] inline const glm::vec3&   Model::getScale         ()                             {return getParent()->getScale();}
        [[nodiscard]] inline const glm::quat&   Model::getRotation      ()                             {return getParent()->getRotation();}
        [[nodiscard]] inline const glm::vec3&   Model::getPosition      ()                             {return getParent()->getPosition();}
        [[nodiscard]] inline       glm::mat4&   Model::getMatrix        ()                             {return getParent()->getMatrix();}
                      inline       void         Model::setPosition      (const glm::vec3& pos)         {getParent()->setPosition(pos);}
                      inline       void         Model::setPosition      (float x, float y, float z)    {getParent()->setPosition(x,y,z);}
                      inline       void         Model::setScale         (const glm::vec3& scale)       {getParent()->setScale(scale);}
                      inline       void         Model::setScale         (float x, float y, float z)    {getParent()->setScale(x,y,z);}
                      inline       void         Model::setRotation      (const glm::quat& qrot)        {getParent()->setRotation(qrot);}
                      inline       void         Model::setRotation      (float rx, float ry, float rz) {getParent()->setRotation(rx,ry,rz);}
                      inline       void         Model::move             (glm::vec3 v)                  {getParent()->move(v);}
                      inline       void         Model::rotate           (glm::quat qrot)               {getParent()->rotate(qrot);}    
                      inline       void         Model::scale            (glm::vec3 v)                  {getParent()->scale(v);}

} // namespace scene::objects