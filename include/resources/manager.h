#pragma once

#include <list>
#include <common/forwards.h>

namespace resources{
    class Manager{
        private:
            std::list<ps<Resource>> resources_;

        public:
                            ps<Model>       addModel        (const std::string& path);
                            ps<Shader>      addShader       (const std::string& path);
                            ps<Texture>     addTexture      (const std::string& path);
            [[nodiscard]]   ps<Resource>    findResource    (const std::string& path);
            [[nodiscard]]   ps<Model>       findModel       (const std::string& path);
            [[nodiscard]]   ps<Shader>      findShader      (const std::string& path);
            [[nodiscard]]   ps<Texture>     findTexture     (const std::string& path);
                
            // Check resources usage and unload useless
            void process();
    };
}