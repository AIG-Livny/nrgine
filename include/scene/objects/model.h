#pragma once

#include <memory>
#include <filesystem>

#include "common/interfaces/IResource.h"
#include "common/interfaces/IMovable.h"
#include "scene/objects/basic.h"
#include "resources/model.h"
#include "resources/shader.h"

namespace scene{
    class Node;
}

namespace scene::objects{
    
class Model : 
    public Basic, 
    public common::IResource,
    public common::IMovable<float>
    {
    private:
        std::shared_ptr<resources::Model>  resource_model_;
        std::shared_ptr<resources::Shader> resource_shader_;
         
    public:
        Model(Node* parent, const std::string& path)
        :
        Basic(parent),
        resource_model_(std::make_unique<resources::Model>(path))
        {}
        
        // IResource
        void setLoaded();
        void setPreloaded();
        void setUnloaded();
        
        inline const std::filesystem::path&         getPath();
        inline const common::IResource::LoadState&  getLoadState();
        
        // IMovable
        [[nodiscard]] inline       glm::vec3    getBackward      ();
        [[nodiscard]] inline       glm::vec3    getForward       ();
        [[nodiscard]] inline       glm::vec3    getLeft          ();
        [[nodiscard]] inline       glm::vec3    getRight         ();
        [[nodiscard]] inline       glm::vec3    getDown          ();
        [[nodiscard]] inline       glm::vec3    getUp            ();
        [[nodiscard]] inline       glm::vec3    getPitch         ();
        [[nodiscard]] inline       glm::vec3    getYaw           ();
        [[nodiscard]] inline       glm::vec3    getRoll          ();
        [[nodiscard]] inline const glm::vec3&   getScale         ();
        [[nodiscard]] inline const glm::quat&   getRotation      ();
        [[nodiscard]] inline const glm::vec3&   getPosition      ();
        [[nodiscard]] inline       glm::mat4&   getMatrix        ();
                      inline       void         setPosition      (const glm::vec3& pos);
                      inline       void         setPosition      (float x, float y, float z);
                      inline       void         setScale         (const glm::vec3& scale);
                      inline       void         setScale         (float x, float y, float z);
                      inline       void         setRotation      (const glm::quat& qrot);
                      inline       void         setRotation      (float rx, float ry, float rz);
                      inline       void         move             (glm::vec3 v);
                      inline       void         rotate           (glm::quat qrot);
                      inline       void         scale            (glm::vec3 v);
                      
};
    
} // END namespace scene::objects