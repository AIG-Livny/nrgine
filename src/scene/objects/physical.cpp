#include "scene/objects/physical.h"

#include "reactphysics3d/reactphysics3d.h"
#include "scene/scene.h"
#include "scene/node.h"

namespace scene::objects{
    
Physical::Physical(Node* parent):
Basic(parent)
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
    
}// namespace scene::objects

/*
#include "scene/objects/basic/physical.h"

#include "application.h"
#include "scene/scene.h"
#include "scene/node.h"

PhysicalObject::PhysicalObject(pwSceneNode parent) : BasicObject(parent){
    
}

PhysicalObject::~PhysicalObject(void){
    auto par = parent.lock();
    auto scn = par->scene.lock();
    scn->physics_world->destroyRigidBody(body);
}
*/