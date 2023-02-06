#pragma once

#include <list>
#include <memory>

#include "common/interfaces/IMovable.h"
#include "common/transform_matrix.h"
#include "scene/objects/common.h"


// #include "scene/objects/model.h"
// #include "scene/objects/physical.h"
// #include "scene/objects/light.h"
// #include "scene/objects/camera.h"

namespace scene {

class Scene;

class Node : public common::IMovable<float> {
    private:
        common::TransformMatrix<float>* matrix_;

        Node*                                      parent_;
        Scene*                                     scene_;
        std::list<std::unique_ptr<Node>>           childs_;
        std::list<std::unique_ptr<objects::Common>> assets_;

    public:
        Node(Node* parent, Scene* scene);

        Node(const Node&)            = delete;
        Node& operator=(const Node&) = delete;


        // IMovable
        [[nodiscard]] inline       glm::vec3    getBackward      ()                             {return matrix_->getBackward();}
        [[nodiscard]] inline       glm::vec3    getForward       ()                             {return matrix_->getForward ();}
        [[nodiscard]] inline       glm::vec3    getLeft          ()                             {return matrix_->getLeft    ();}
        [[nodiscard]] inline       glm::vec3    getRight         ()                             {return matrix_->getRight   ();}
        [[nodiscard]] inline       glm::vec3    getDown          ()                             {return matrix_->getDown    ();}
        [[nodiscard]] inline       glm::vec3    getUp            ()                             {return matrix_->getUp      ();}
        [[nodiscard]] inline       glm::vec3    getPitch         ()                             {return matrix_->getPitch   ();}
        [[nodiscard]] inline       glm::vec3    getYaw           ()                             {return matrix_->getPitch   ();}
        [[nodiscard]] inline       glm::vec3    getRoll          ()                             {return matrix_->getRoll    ();}
        [[nodiscard]] inline const glm::vec3&   getScale         ()                             {return matrix_->getScale();}
        [[nodiscard]] inline const glm::quat&   getRotation      ()                             {return matrix_->getRotation();}
        [[nodiscard]] inline const glm::vec3&   getPosition      ()                             {return matrix_->getPosition();}
        [[nodiscard]] inline       glm::mat4&   getMatrix        ()                             {return matrix_->getMatrix();}
                      inline       void         setPosition      (const glm::vec3& pos)         {matrix_->setPosition(pos);}
                      inline       void         setPosition      (float x, float y, float z)    {matrix_->setPosition(x,y,z);}
                      inline       void         setScale         (const glm::vec3& scale)       {matrix_->setScale(scale);}
                      inline       void         setScale         (float x, float y, float z)    {matrix_->setScale(x,y,z);}
                      inline       void         setRotation      (const glm::quat& qrot)        {matrix_->setRotation(qrot);}
                      inline       void         setRotation      (float rx, float ry, float rz) {matrix_->setRotation(rx,ry,rz);}
                      inline       void         move             (glm::vec3 v)                  {matrix_->move(v);}
                      inline       void         rotate           (glm::quat qrot)               {matrix_->rotate(qrot);}    
                      inline       void         scale            (glm::vec3 v)                  {matrix_->scale(v);}
        // END IMovable              
        
        [[nodiscard]] inline const auto& getChilds()   { return childs_; }
        [[nodiscard]] inline       auto* getParent()   { return parent_; }
        [[nodiscard]] inline       auto* getScene()    { return scene_; }

        Node&           createChildNode();
 
        template<int Tid>
        std::list<objects::Common*>& getObjects(){
            static std::list<objects::Common*> objectsList;
            return objectsList;
        }
    
        template<int Tid>
        objects::Common& create(){
            assets_.push_back(objects::TFactory::Create(Tid, this));
            getObjects<Tid>().push_back(assets_.end()->get());
            return *assets_.back();
        }
 
        //objects::Model&     createModel     (std::string path);
        //objects::Physical&  createPhysical  ();
        //objects::Light&     createLight     ();
        //objects::Camera&    createCamera    ();
};

} // namespace scene