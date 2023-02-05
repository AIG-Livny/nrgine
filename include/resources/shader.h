#pragma once

#include <string>
#include <glm/glm.hpp>
#include "resources/resource.h"

namespace resources{

class Shader : public Resource{
    private:
        glm::u32     handlerGPU_ = 0;
        std::unique_ptr<std::string>  vertexShader_      = std::make_unique<std::string>("");
        std::unique_ptr<std::string>  geometryShader_    = std::make_unique<std::string>("");
        std::unique_ptr<std::string>  fragmentShader_    = std::make_unique<std::string>("");
        
        void loadToRAM();
        void loadToGPU();

    public:
        Shader(const std::filesystem::path& path);
        
        [[nodiscard]] inline const auto& getVertexShader()     {return *vertexShader_;}
        [[nodiscard]] inline const auto& getFragmentShader()   {return *fragmentShader_;}
        [[nodiscard]] inline const auto& getGeometryShader()   {return *geometryShader_;}
        [[nodiscard]] inline const auto& getHandler()          {return handlerGPU_;}
        
        void setLoaded();
        void setPreloaded();
        void setUnloaded();
        
        void setBool    (const std::string& name, bool value);
        void setInt     (const std::string& name, int value);
        void setFloat   (const std::string& name, float value);
        void setVec2    (const std::string& name, glm::vec2 value);
        void setVec2    (const std::string& name, float x, float y); 
        void setVec3    (const std::string& name, glm::vec3 value);
        void setVec3    (const std::string& name, float x, float y, float z); 
        void setVec4    (const std::string& name, glm::vec4 value);
        void setVec4    (const std::string& name, float x, float y, float z, float w); 
        void setMat2    (const std::string& name, glm::mat2& mat);
        void setMat3    (const std::string& name, glm::mat3& mat);
        void setMat4    (const std::string& name, glm::mat4& mat);
};

} // END namespace resources
