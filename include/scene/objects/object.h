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

        [[nodiscard]] Node* getParent() const {return parent_;} 
        virtual Type getType() const = 0;
        
        // IMovable
        [[nodiscard]]       glm::vec3    getBackward  () const                       override;
        [[nodiscard]]       glm::vec3    getForward   () const                       override;
        [[nodiscard]]       glm::vec3    getLeft      () const                       override;
        [[nodiscard]]       glm::vec3    getRight     () const                       override;
        [[nodiscard]]       glm::vec3    getDown      () const                       override;
        [[nodiscard]]       glm::vec3    getUp        () const                       override;
        [[nodiscard]]       glm::vec3    getPitch     () const                       override;
        [[nodiscard]]       glm::vec3    getYaw       () const                       override;
        [[nodiscard]]       glm::vec3    getRoll      () const                       override;
        [[nodiscard]] const glm::vec3&   getScale     () const                       override;
        [[nodiscard]] const glm::quat&   getRotation  () const                       override;
        [[nodiscard]] const glm::vec3&   getPosition  () const                       override;
        [[nodiscard]]       glm::mat4&   getMatrix    ()                             override;
                            void         setPosition  (const glm::vec3& pos)         override;
                            void         setPosition  (float x, float y, float z)    override;
                            void         setScale     (const glm::vec3& scale)       override;
                            void         setScale     (float x, float y, float z)    override;
                            void         setRotation  (const glm::quat& qrot)        override;
                            void         setRotation  (float rx, float ry, float rz) override;
                            void         move         (glm::vec3 v)                  override;
                            void         rotate       (glm::quat qrot)               override;
                            void         scale        (glm::vec3 v)                  override;
};

using TFactory = common::Factory<Object, Node*>;

} // namespace scene::objects