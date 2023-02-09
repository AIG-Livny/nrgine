#include "scene/objects/physical.h"
FACTORY_CLASS_REGISTER(scene::objects::TFactory, scene::objects::TPhysical, scene::objects::Physical);

#include "reactphysics3d/reactphysics3d.h"
#include "scene/scene.h"
#include "scene/node.h"

namespace scene::objects{
    
TPhysical::TPhysical(Node* parent):
Object(parent)
{
    const glm::quat& glq = getParent()->getRotation();
    reactphysics3d::Quaternion  rqu(glq.x, glq.y, glq.z, glq.w);
    rqu.normalize();
    const glm::vec3& glp = getParent()->getPosition();
    reactphysics3d::Vector3 rve(glp.x, glp.y, glp.z);
    reactphysics3d::Transform transform = reactphysics3d::Transform(rve, rqu);
    
    //transform.setFromOpenGL((reactphysics3d::decimal*)&par->matrix);
    body_ = getParent()->getScene()->getPhysicsWorld()->createRigidBody(transform);
    
    
}
    
TPhysical::~TPhysical(void){
    getParent()->getScene()->getPhysicsWorld()->destroyRigidBody(body_);
}
    
}// namespace scene::objects