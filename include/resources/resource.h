#pragma once

#include <string>
#include <filesystem>

namespace resources{
    enum LoadState{
        NotLoaded,
        PreLoaded,
        Loaded
    };

    class Resource{
        private:
            std::filesystem::path path_;
        
            virtual void setLoaded      () = 0;
            virtual void setPreloaded   () = 0;
            virtual void setUnloaded    () = 0;

        protected:
            LoadState loadState = LoadState::NotLoaded;
            
        public:
            Resource(const std::string& path): path_(path){};
            Resource(const std::filesystem::path& path): path_(path){};

            [[nodiscard]] inline const auto&    getPath        (){return path_         ;};
            [[nodiscard]] inline       auto     getLoadState   (){return loadState     ;};
    };
}