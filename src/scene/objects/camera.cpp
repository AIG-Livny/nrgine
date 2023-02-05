#include "scene/objects/camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "scene/node.h"

namespace scene::objects{
    
Camera::Camera(Node* parent):
Basic(parent)
{
    calculateProjection();
}
    
void Camera::calculateProjection(void){
    projection_ = glm::perspective(glm::radians(fieldOfView_), aspect_, near_, far_);
}   

void Camera::setFov(float f){
    fieldOfView_ = f;
    calculateProjection();
}
    
void Camera::setAspect(float f){
    aspect_ = f;
    calculateProjection();
}

void Camera::setNear(float f){
    near_ = f;
    calculateProjection();
}

void Camera::setFar(float f){
    far_ = f;
    calculateProjection();
}

inline const glm::mat4& Camera::getProjection(void){
    return projection_;
}

inline const glm::mat4& Camera::getView(void){
    view_ = glm::lookAt(
        getParent()->getPosition(),
        getParent()->getPosition() + getParent()->getForward(),
        getParent()->getUp()
        );
    return view_;
}

} // namespace scene::objects

/*
#include "scene/objects/basic/camera.h"

#include <memory>

#include "scene/node.h"
#include "scene/objects/basic/basic_object.h"


*/