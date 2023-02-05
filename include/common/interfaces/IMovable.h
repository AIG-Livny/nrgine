#pragma once

#include <glm/glm.hpp>

namespace common{    
    
template <typename T>
concept GLMCompatible = (
    std::is_same<T,float>::value || 
    std::is_same<T,double>::value ||
    std::is_same<T,int>::value);

template <typename T>
using vect      = glm::vec<3, T,    glm::defaultp>;

template <typename T>
using vect4      = glm::vec<4, T,    glm::defaultp>;

template <typename T>
using matr      = glm::mat<4, 4, T, glm::defaultp>;

template <typename T>
using quater    = glm::qua<T,       glm::defaultp>;

template<typename T> requires GLMCompatible<T>
class IMovable{
    virtual         vect<T>     getBackward () = 0;
    virtual         vect<T>     getForward  () = 0;
    virtual         vect<T>     getLeft     () = 0;
    virtual         vect<T>     getRight    () = 0;
    virtual         vect<T>     getDown     () = 0;
    virtual         vect<T>     getUp       () = 0;
    
    virtual         vect<T>     getPitch    () = 0;
    virtual         vect<T>     getYaw      () = 0;
    virtual         vect<T>     getRoll     () = 0;
    virtual const   vect<T>&    getScale    () = 0;
    virtual const   quater<T>&  getRotation () = 0;
    virtual const   vect<T>&    getPosition () = 0;
    virtual         matr<T>&    getMatrix   () = 0;
    
    virtual void setPosition        (const vect<T>& pos)    = 0;
    virtual void setPosition        (T x, T y, T z)         = 0;
    virtual void setScale           (const vect<T>& scale)  = 0;
    virtual void setScale           (T x, T y, T z)         = 0;
    virtual void setRotation        (const quater<T>& qrot) = 0;
    virtual void setRotation        (T rx, T ry, T rz)      = 0;
    
    virtual void move               (vect<T> v)             = 0;
    virtual void rotate             (quater<T> qrot)        = 0;
    virtual void scale              (vect<T> v)             = 0;

    public:
      
    constexpr static vect<T> worldForward  = vect<T>( 0, 0,-1 );
    constexpr static vect<T> worldBackward = vect<T>( 0, 0, 1 );
    constexpr static vect<T> worldLeft     = vect<T>(-1, 0, 0 );
    constexpr static vect<T> worldRight    = vect<T>( 1, 0, 0 );
    constexpr static vect<T> worldUp       = vect<T>( 0, 1, 0 );
    constexpr static vect<T> worldDown     = vect<T>( 0,-1, 0 );
    constexpr static vect<T> worldPitch    = worldRight;
    constexpr static vect<T> worldYaw      = worldUp;
    constexpr static vect<T> worldRoll     = worldBackward;
    
    //virtual IMovable& operator=(const matr& m) = 0;
};
    
} // END namespace common