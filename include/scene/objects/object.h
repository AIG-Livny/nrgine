#pragma once

#include "common/factory.h"
#include "common/interfaces/IMovable.h"

namespace scene{
    class Node;
}

namespace scene::objects{

enum Type{
    Camera,
    Light,
    Model,
    Physical,
    SIZE,
    NONE,
};

class Object :  public common::IMovable<float>{
    private:
        Node* parent_;

    public:
        Object(Node* parent)
        : 
        parent_(parent)
        {}
        
        // Copy denied
        Object(const Object&)             = delete;
        Object& operator=(const Object&)  = delete;

        [[nodiscard]] inline Node* getParent()  {return parent_;} 
        virtual Type getType() = 0;
        
        // IMovable
        [[nodiscard]]       glm::vec3    getBackward  ()                             ;
        [[nodiscard]]       glm::vec3    getForward   ()                             ;
        [[nodiscard]]       glm::vec3    getLeft      ()                             ;
        [[nodiscard]]       glm::vec3    getRight     ()                             ;
        [[nodiscard]]       glm::vec3    getDown      ()                             ;
        [[nodiscard]]       glm::vec3    getUp        ()                             ;
        [[nodiscard]]       glm::vec3    getPitch     ()                             ;
        [[nodiscard]]       glm::vec3    getYaw       ()                             ;
        [[nodiscard]]       glm::vec3    getRoll      ()                             ;
        [[nodiscard]] const glm::vec3&   getScale     ()                             ;
        [[nodiscard]] const glm::quat&   getRotation  ()                             ;
        [[nodiscard]] const glm::vec3&   getPosition  ()                             ;
        [[nodiscard]]       glm::mat4&   getMatrix    ()                             ;
                            void         setPosition  (const glm::vec3& pos)         ;
                            void         setPosition  (float x, float y, float z)    ;
                            void         setScale     (const glm::vec3& scale)       ;
                            void         setScale     (float x, float y, float z)    ;
                            void         setRotation  (const glm::quat& qrot)        ;
                            void         setRotation  (float rx, float ry, float rz) ;
                            void         move         (glm::vec3 v)                  ;
                            void         rotate       (glm::quat qrot)               ;
                            void         scale        (glm::vec3 v)                  ;
};

using TFactory = common::Factory<Object, Node*>;

} // namespace scene::objects