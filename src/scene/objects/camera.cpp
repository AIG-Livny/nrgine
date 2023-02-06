#include "scene/objects/camera.h"
FACTORY_CLASS_REGISTER(scene::objects::TFactory, scene::objects::TCamera, scene::objects::Camera);

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "scene/node.h"

namespace scene::objects{
    
TCamera::TCamera(Node* parent):
Common(parent)
{
    calculateProjection();
}
    
void TCamera::calculateProjection(void){
    projection_ = glm::perspective(glm::radians(fieldOfView_), aspect_, near_, far_);
}   

void TCamera::setFov(float f){
    fieldOfView_ = f;
    calculateProjection();
}
    
void TCamera::setAspect(float f){
    aspect_ = f;
    calculateProjection();
}

void TCamera::setNear(float f){
    near_ = f;
    calculateProjection();
}

void TCamera::setFar(float f){
    far_ = f;
    calculateProjection();
}

inline const glm::mat4& TCamera::getProjection(void){
    return projection_;
}

inline const glm::mat4& TCamera::getView(void){
    view_ = glm::lookAt(
        getParent()->getPosition(),
        getParent()->getPosition() + getParent()->getForward(),
        getParent()->getUp()
        );
    return view_;
}

} // namespace scene::objects