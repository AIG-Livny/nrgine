#include "scene/scene.h"

#include "application.h"
#include "reactphysics3d/reactphysics3d.h"
#include "scene/node.h"

namespace scene{
    inline const auto& Scene::getPhysicsCommon(){
        return application_->getPhysicsCommon();
    }
    
    Scene::Scene(Application* app)
    :
    application_(app),
    rootNode_(std::make_unique<Node>(nullptr, this)),
    physicsWorld_(getPhysicsCommon()->createPhysicsWorld())
    {}
    
    Scene::~Scene(){
        getPhysicsCommon()->destroyPhysicsWorld(physicsWorld_);
    };
    
    void Scene::UpdatePhysics(const float& delta){
        //physicsWorld_->update(delta);
        //    for(auto o : physical_objects){
        //auto par = o->parent.lock();
        //auto oldscale = par->GetScale();
        //o->body->getTransform().getOpenGLMatrix((reactphysics3d::decimal*)&(par->matrix));
        //par->SetScale(oldscale);
        //}
    }
    
}