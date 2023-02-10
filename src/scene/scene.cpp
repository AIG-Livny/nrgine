#include "scene/scene.h"

#include "interfaces/IApplication.h"
#include "reactphysics3d/reactphysics3d.h"
#include "scene/node.h"
#include "scene/objects/physical.h"

namespace scene{
    inline const auto& Scene::getPhysicsCommon(){
        return application_->getPhysicsCommon();
    }
    
    Scene::Scene(IApplication* app)
    :
    application_(app),
    rootNode_(std::make_unique<Node>(nullptr, this)),
    physicsWorld_(getPhysicsCommon()->createPhysicsWorld()),
    objects_(objects::Type::SIZE)
    {}
    
    Scene::~Scene(){
        getPhysicsCommon()->destroyPhysicsWorld(physicsWorld_);
    };
    
    void Scene::UpdatePhysics(const float& delta){
        physicsWorld_->update(delta);
        for(auto o : objects_[objects::Physical]){
            auto ob = static_cast<objects::TPhysical*>(o);
            ob->getBody()->getTransform().getOpenGLMatrix((reactphysics3d::decimal*)&(ob->getParent()->getMatrix()));
        }
    }
    
}