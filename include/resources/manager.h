#pragma once

#include <list>

#include "resources/model.h"
#include "resources/shader.h"

namespace resources{

class Manager{
    private:
        std::list<std::shared_ptr<Resource>> resources_;

    public:
                        std::shared_ptr<Model>       addModel        (const std::string& path);
                        std::shared_ptr<Shader>      addShader       (const std::string& path);
        //                std::shared_ptr<Texture>     addTexture      (const std::string& path);
        [[nodiscard]]   std::shared_ptr<Resource>    findResource    (const std::string& path);
        [[nodiscard]]   std::shared_ptr<Model>       findModel       (const std::string& path);
        [[nodiscard]]   std::shared_ptr<Shader>      findShader      (const std::string& path);
        //[[nodiscard]]   std::shared_ptr<Texture>     findTexture     (const std::string& path);
            
        // Check resources usage and unload useless
        void process();
};

} // END namespace resources