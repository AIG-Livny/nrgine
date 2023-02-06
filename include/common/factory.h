#pragma once

#include <memory>
#include <map>
#include <stdexcept>

namespace common{
/*
    Factory used for automatic register new class derived from common 
    base class, and creating them by id or typename. It separates building manager/classes. 
    
    Define TMyFactory, example:     using TMyFactory = common::Factory<MyClassBase, void*>
    where after "MyClassBase" any number of arguments constructor MyClassBase.
    It's necessary for macro expansion FACTORY_CLASS_REGISTER where you can't use commas.
    
    To register a new class paste FACTORY_CLASS_REGISTER(FACTORY, CLASS, NUM)
    next to the #include "myclass.h" in the myclass.cpp, example: 
        #include "myclass.h"
        FACTORY_CLASS_REGISTER(TMyFactory, MyClass, MyEnum::MyClass)
    
    For creating use: examle: TMyFactory::Create(MyEnum::MyClass, nullptr)
*/
template<class _Base, class... _Args>
class Factory{    
    using CreatorT  = std::unique_ptr<_Base> (*)(_Args...);
    using MapT      = std::map<int, CreatorT>;
    
    private:
        inline static MapT& getMap(){
            static MapT mmap;
            return mmap;
        }
        
        template<class _Object>
        class Register{
            public:
                static CreatorT creator;
                static std::unique_ptr<_Base> Create(_Args... args){return std::make_unique<_Object>(args...);}    
                static CreatorT initCreator(int i){
                    getMap()[i] = Create;
                    return Create;
                }
        };    

    public:
        [[nodiscard]] inline static std::unique_ptr<_Base> Create(int i,_Args... args){ 
            auto iter = getMap().find(i);
            if(iter == getMap().end()){ 
                throw std::range_error("Class not found"); 
            }
            return iter->second(args...);    
        }
        
        [[nodiscard]] inline static std::size_t size(){return getMap().size();}
};

/*
    Register class in factory
    @param FACTORY  - TMyFactory
    @param CLASS    - MyClass derived from MyClassBase
    @param NUM      - unique int id of class. It can be enum
*/
#define FACTORY_CLASS_REGISTER(FACTORY, CLASS, NUM) template<>template<>FACTORY::CreatorT FACTORY::Register<CLASS>::creator = FACTORY::Register<CLASS>::initCreator(NUM);

} // namespace common