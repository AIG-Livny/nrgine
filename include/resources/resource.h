#pragma once

#include <string>
#include <filesystem>

#include "common/interfaces/IResource.h"

namespace resources{

class Resource : public common::IResource{
    private:
        std::filesystem::path path_;
    
    protected:
        LoadState loadState = LoadState::NotLoaded;
        
    public:
        Resource(const std::string& path): path_(path){};
        Resource(const std::filesystem::path& path): path_(path){};

        Resource(const Resource&)               = delete;
        Resource& operator=(const Resource&)    = delete;

        [[nodiscard]] inline const std::filesystem::path&           getPath        (){return path_    ;};
        [[nodiscard]] inline const common::IResource::LoadState&    getLoadState   (){return loadState;};
};

} // END namespace resources