#pragma once

#include <memory>
#include <filesystem>

#include "common/interfaces/IResource.h"
#include "scene/node.h"
#include "scene/objects/object.h"
#include "resources/model.h"
#include "resources/shader.h"

namespace scene{
    class Node;
}

namespace scene::objects{
    
class TModel : 
    public Object, 
    public common::IResource
    {
    private:
        std::shared_ptr<resources::Model>  resourceModel_;
        std::shared_ptr<resources::Shader> resourceShader_;
         
    public:
        TModel(Node* parent);
        
        void setModel (std::shared_ptr<resources::Model>  model ){resourceModel_  = model; }
        void setShader(std::shared_ptr<resources::Shader> shader){resourceShader_ = shader;}
        [[nodiscard]] auto getModel ()   {return resourceModel_; }
        [[nodiscard]] auto getShader ()  {return resourceShader_; }
        
        // Object
        [[nodiscard]] Type getType() const override {return Type::Model;}
        
        // IResource
        void setLoaded()    override;
        void setPreloaded() override;
        void setUnloaded()  override;
        
        const std::filesystem::path&         getPath()      override;
        const common::IResource::LoadState&  getLoadState() override;             
};
    
} // END namespace scene::objects