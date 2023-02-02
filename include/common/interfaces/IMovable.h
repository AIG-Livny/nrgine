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
    using matr      = glm::mat<4, 4, T, glm::defaultp>;
    
    template <typename T>
    using quater    = glm::qua<T,       glm::defaultp>;
    
    template<typename T> requires GLMCompatible<T>
    class IMovable{
        virtual vect<T>    getBackward () = 0;
        virtual vect<T>    getForward  () = 0;
        virtual vect<T>    getLeft     () = 0;
        virtual vect<T>    getRight    () = 0;
        virtual vect<T>    getDown     () = 0;
        virtual vect<T>    getUp       () = 0;
        virtual vect<T>    getPosition () = 0;
        virtual vect<T>    getScale    () = 0;
        virtual matr<T>&   getMatrix   () = 0;

        virtual void setPosition        (const vect<T>& pos)   = 0;
        virtual void setPosition        (T x, T y, T z)         = 0;
        virtual void setScale           (const vect<T>& scale) = 0;
        virtual void setScale           (T x, T y, T z)         = 0;
        virtual void setRotation        (const quater<T>& qrot) = 0;
        virtual void setRotation        (T rx, T ry, T rz)      = 0;

        virtual void move               (vect<T> v) = 0;
        virtual void moveUp             (T u) = 0;
        virtual void moveDown           (T u) = 0;
        virtual void moveLeft           (T u) = 0;
        virtual void moveRight          (T u) = 0;
        virtual void moveForward        (T u) = 0;
        virtual void moveBackward       (T u) = 0;

        virtual void rotate             (quater<T> qrot) = 0;
        virtual void rotatePitchUp      (T u) = 0;
        virtual void rotatePitchDown    (T u) = 0;
        virtual void rotateYawLeft      (T u) = 0;
        virtual void rotateYawRight     (T u) = 0;
        virtual void rotateRollLeft     (T u) = 0;
        virtual void rotateRollRight    (T u) = 0;
        
        public:
          
        constexpr static auto worldForward   = vect<T>( 0, 0,-1 );
        constexpr static auto worldBackward  = vect<T>( 0, 0, 1 );
        constexpr static auto worldLeft      = vect<T>(-1, 0, 0 );
        constexpr static auto worldRight     = vect<T>( 1, 0, 0 );
        constexpr static auto worldUp        = vect<T>( 0, 1, 0 );
        constexpr static auto worldDown      = vect<T>( 0,-1, 0 );
        
        //virtual IMovable& operator=(const matr& m) = 0;
    };
}