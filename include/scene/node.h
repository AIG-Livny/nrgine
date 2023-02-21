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
        [[nodiscard]]       glm::vec3    getBackward ()                            const override {return matrix_.getBackward();}
        [[nodiscard]]       glm::vec3    getForward  ()                            const override {return matrix_.getForward ();}
        [[nodiscard]]       glm::vec3    getLeft     ()                            const override {return matrix_.getLeft    ();}
        [[nodiscard]]       glm::vec3    getRight    ()                            const override {return matrix_.getRight   ();}
        [[nodiscard]]       glm::vec3    getDown     ()                            const override {return matrix_.getDown    ();}
        [[nodiscard]]       glm::vec3    getUp       ()                            const override {return matrix_.getUp      ();}
        [[nodiscard]]       glm::vec3    getPitch    ()                            const override {return matrix_.getPitch   ();}
        [[nodiscard]]       glm::vec3    getYaw      ()                            const override {return matrix_.getPitch   ();}
        [[nodiscard]]       glm::vec3    getRoll     ()                            const override {return matrix_.getRoll    ();}
        [[nodiscard]] const glm::vec3&   getScale    ()                            const override {return matrix_.getScale();}
        [[nodiscard]] const glm::quat&   getRotation ()                            const override {return matrix_.getRotation();}
        [[nodiscard]] const glm::vec3&   getPosition ()                            const override {return matrix_.getPosition();}
        [[nodiscard]]       glm::mat4&   getMatrix   ()                                  override {return matrix_.getMatrix();}
                            void         setPosition (const glm::vec3& pos)              override {matrix_.setPosition(pos);}
                            void         setPosition (float x, float y, float z)         override {matrix_.setPosition(x,y,z);}
                            void         setScale    (const glm::vec3& scale)            override {matrix_.setScale(scale);}
                            void         setScale    (float x, float y, float z)         override {matrix_.setScale(x,y,z);}
                            void         setRotation (const glm::quat& qrot)             override {matrix_.setRotation(qrot);}
                            void         setRotation (float rx, float ry, float rz)      override {matrix_.setRotation(rx,ry,rz);}
                            void         move        (glm::vec3 v)                       override {matrix_.move(v);}
                            void         rotate      (glm::quat qrot)                    override {matrix_.rotate(qrot);}    
                            void         scale       (glm::vec3 v)                       override {matrix_.scale(v);}
        // END IMovable              
        
        [[nodiscard]] const auto& getChilds()   { return childs_; }
        [[nodiscard]]       auto* getParent()   { return parent_; }
        [[nodiscard]]       auto* getScene()    { return scene_; }

        Node&           createChildNode();
 
        objects::Object& createObject(objects::Type t);
};

} // namespace scene