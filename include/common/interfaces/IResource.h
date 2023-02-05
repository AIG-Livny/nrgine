#pragma once

#include <filesystem>

namespace common{

class IResource{
    public:
        enum LoadState{
            NotLoaded,
            PreLoaded,
            Loaded
        };
    
    private:    
        virtual void setLoaded      () = 0;
        virtual void setPreloaded   () = 0;
        virtual void setUnloaded    () = 0;

        virtual inline const std::filesystem::path& getPath     () = 0;
        virtual inline const LoadState&             getLoadState() = 0;
};

} // END namespace common