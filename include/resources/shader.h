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
        
        void setBool    (const char* name, const bool value);
        void setInt     (const char* name, const int value);
        void setFloat   (const char* name, const float value);
        void setVec2    (const char* name, const glm::vec2& value);
        void setVec2    (const char* name, const float x, const float y); 
        void setVec3    (const char* name, const glm::vec3& value);
        void setVec3    (const char* name, const float x, const float y, const float z); 
        void setVec4    (const char* name, const glm::vec4& value);
        void setVec4    (const char* name, const float x, const float y, const float z, const float w); 
        void setMat2    (const char* name, const glm::mat2& mat);
        void setMat3    (const char* name, const glm::mat3& mat);
        void setMat4    (const char* name, const glm::mat4& mat);
};

} // namespace resources
