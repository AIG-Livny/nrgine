#pragma once

#include <list>
#include <memory>

#include "common/interfaces/IMovable.h"
#include "common/transform_matrix.h"
#include "scene/objects/object.h"

namespace scene {

class Scene;

class Node : public common::IMovable<float> {
    private:
        common::TransformMatrix<float>             matrix_;

        Node*                                      parent_;
        Scene*                                     scene_;
        std::list<std::unique_ptr<Node>>           childs_;
        std::list<std::unique_ptr<objects::Object>> assets_;

    public:
        Node(Node* parent, Scene* scene);

        // Copy denied
        Node(const Node&)            = delete;
        Node& operator=(const Node&) = delete;

        // IMovable
        [[nodiscard]] inline       glm::vec3    getBackward ()                             override {return matrix_.getBackward();}
        [[nodiscard]] inline       glm::vec3    getForward  ()                             override {return matrix_.getForward ();}
        [[nodiscard]] inline       glm::vec3    getLeft     ()                             override {return matrix_.getLeft    ();}
        [[nodiscard]] inline       glm::vec3    getRight    ()                             override {return matrix_.getRight   ();}
        [[nodiscard]] inline       glm::vec3    getDown     ()                             override {return matrix_.getDown    ();}
        [[nodiscard]] inline       glm::vec3    getUp       ()                             override {return matrix_.getUp      ();}
        [[nodiscard]] inline       glm::vec3    getPitch    ()                             override {return matrix_.getPitch   ();}
        [[nodiscard]] inline       glm::vec3    getYaw      ()                             override {return matrix_.getPitch   ();}
        [[nodiscard]] inline       glm::vec3    getRoll     ()                             override {return matrix_.getRoll    ();}
        [[nodiscard]] inline const glm::vec3&   getScale    ()                             override {return matrix_.getScale();}
        [[nodiscard]] inline const glm::quat&   getRotation ()                             override {return matrix_.getRotation();}
        [[nodiscard]] inline const glm::vec3&   getPosition ()                             override {return matrix_.getPosition();}
        [[nodiscard]] inline       glm::mat4&   getMatrix   ()                             override {return matrix_.getMatrix();}
                      inline       void         setPosition (const glm::vec3& pos)         override {matrix_.setPosition(pos);}
                      inline       void         setPosition (float x, float y, float z)    override {matrix_.setPosition(x,y,z);}
                      inline       void         setScale    (const glm::vec3& scale)       override {matrix_.setScale(scale);}
                      inline       void         setScale    (float x, float y, float z)    override {matrix_.setScale(x,y,z);}
                      inline       void         setRotation (const glm::quat& qrot)        override {matrix_.setRotation(qrot);}
                      inline       void         setRotation (float rx, float ry, float rz) override {matrix_.setRotation(rx,ry,rz);}
                      inline       void         move        (glm::vec3 v)                  override {matrix_.move(v);}
                      inline       void         rotate      (glm::quat qrot)               override {matrix_.rotate(qrot);}    
                      inline       void         scale       (glm::vec3 v)                  override {matrix_.scale(v);}
        // END IMovable              
        
        [[nodiscard]] inline const auto& getChilds()   { return childs_; }
        [[nodiscard]] inline       auto* getParent()   { return parent_; }
        [[nodiscard]] inline       auto* getScene()    { return scene_; }

        Node&           createChildNode();
 
        objects::Object& createObject(objects::Type t);
};

} // namespace scene