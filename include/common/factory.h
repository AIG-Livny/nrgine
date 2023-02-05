#pragma once

#include <memory>
#include <map>

namespace common{

template<class _Base>
class Factory{    
    using CreatorT  = std::unique_ptr<_Base> (*)(void*);
    using MapT      = std::map<const char*, CreatorT>;
    
    private:
        inline static MapT& getMap(){
            static MapT mmap;
            return mmap;
        }
        
        template<class _Object>
        class Register{
            public:
                static CreatorT creator;
                static std::unique_ptr<_Base> Create(void* parent){return std::make_unique<_Object>(parent);}    
                static CreatorT initCreator(){
                    getMap()[typeid(_Object).name()] = Create;
                    return Create;
                }
        };    

    public:
        template<class _Object>
        static std::unique_ptr<_Base> Create(void* parent){ 
            auto iter = getMap().find(typeid(_Object).name());
            if(iter == getMap().end()) return nullptr;
            return iter->second(parent);    
        }
};

/*
    Register class in factory
    @param BASE  - MyClassBase
    @param CLASS - MyClass derived from MyClassBase
*/
#define FACTORY_CLASS_REGISTER(BASE, CLASS) template<>template<>common::Factory<BASE>::CreatorT common::Factory<BASE>::Register<CLASS>::creator = common::Factory<BASE>::Register<CLASS>::initCreator();

} // namespace common