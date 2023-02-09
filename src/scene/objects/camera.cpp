#include "scene/objects/camera.h"
FACTORY_CLASS_REGISTER(scene::objects::TFactory, scene::objects::TCamera, scene::objects::Camera);

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "scene/node.h"

namespace scene::objects{
        
const glm::mat4& TCamera::getView(void){
    view_ = glm::lookAt(
        getParent()->getPosition(),
        getParent()->getPosition() + getParent()->getForward(),
        getParent()->getUp()
        );
    return view_;
}

} // namespace scene::objects