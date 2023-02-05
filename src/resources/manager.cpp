#include "resources/manager.h"

#include <algorithm>
#include <memory>

#include "resources/resource.h"
#include "resources/model.h"
#include "resources/shader.h"

namespace resources{
    // TODO Consider change container to hashable if necessary
    std::shared_ptr<Resource> Manager::findResource(const std::string& path){
        for(auto& r : resources_){  
            if(r->getPath() == path){
                return r;
            }
        }
        return nullptr;
    }
    
    // TODO By Type
    std::shared_ptr<Model> Manager::findModel(const std::string& path){
        return std::static_pointer_cast<Model>(findResource(path));
    }
    
    std::shared_ptr<Shader> Manager::findShader(const std::string& path){
        return std::static_pointer_cast<Shader>(findResource(path));
    }
    
    std::shared_ptr<Model> Manager::addModel(const std::string& path){
        if(auto a = findResource(path)){return std::static_pointer_cast<Model>(a);}
        auto m = std::make_shared<Model>(path);
        resources_.push_back(std::static_pointer_cast<Resource>(m));
        return m;
    }
    
    std::shared_ptr<Shader> Manager::addShader(const std::string& path){
        if(auto a = findResource(path)){return std::static_pointer_cast<Shader>(a);}
        auto m = std::make_shared<Shader>(path);
        resources_.push_back(std::static_pointer_cast<Resource>(m));
        return m;
    }
}