#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "common/forwards.h"
#include "resources/resource.h"

namespace resources{
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;
    };

    struct Mesh{
        // RAM representation
        pu<std::vector<Vertex>> vertices;
        pu<std::vector<glm::u32>> indices;

        // GPU representation
        glm::u32 vertexArrayObject    = 0;
        glm::u32 vertexBufferObject   = 0;
        glm::u32 elementBufferObject  = 0;
        glm::u32 indices_num;
    };

 
    class Model : public Resource{
        private:
            std::unique_ptr<std::vector<Mesh>> meshes_;        
            void loadRAM();
            void loadGPU();
            void unloadGPU();
            
        public:
            Model(const std::filesystem::path& path);

            void setLoaded();
            void setPreloaded();
            void setUnloaded();

            [[nodiscard]] inline const auto& getMeshes() {return *meshes_;}

            //vector<Mesh>::iterator begin();
            //vector<Mesh>::iterator end();
            //vector<Mesh>::const_iterator begin() const;
            //vector<Mesh>::const_iterator end() const;
            //vector<Mesh>::const_iterator cbegin();
            //vector<Mesh>::const_iterator cend();
    };
}