#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "common/interfaces/IMovable.h"

namespace common{
    template <typename T>
    class TransformMatrix :IMovable<T>{
        private:
            matr<T> matrix_;
            
        public:
            
            [[nodiscard]] vect<T>    getBackward ();
            [[nodiscard]] vect<T>    getForward  ();
            [[nodiscard]] vect<T>    getLeft     ();
            [[nodiscard]] vect<T>    getRight    ();
            [[nodiscard]] vect<T>    getDown     ();
            [[nodiscard]] vect<T>    getUp       ();
            [[nodiscard]] vect<T>    getPosition ();
            [[nodiscard]] vect<T>    getScale    ();
            [[nodiscard]] matr<T>&   getMatrix   ();

            void setPosition        (const vect<T>& pos);
            void setPosition        (T x, T y, T z);
            void setScale           (const vect<T>& scale);
            void setScale           (T x, T y, T z);
            void setRotation        (const quater<T>& qrot);
            void setRotation        (T rx, T ry, T rz);

            void moveUp             (T u);
            void moveDown           (T u);
            void moveLeft           (T u);
            void moveRight          (T u);
            void moveForward        (T u);
            void moveBackward       (T u);
            void rotatePitchUp      (T u);
            void rotatePitchDown    (T u);
            void rotateYawLeft      (T u);
            void rotateYawRight     (T u);
            void rotateRollLeft     (T u);
            void rotateRollRight    (T u);
    };
 
    template <typename T>
    vect<T> TransformMatrix<T>::getBackward(){
        constexpr auto v4 = glm::vec4(IMovable<T>::worldBackward, 0);
        return matrix_ * v4;
    }
    
    
    template <typename T>
    vect<T> TransformMatrix<T>::getForward(){
        constexpr auto v4 = glm::vec4(IMovable<T>::worldForward, 0);
        return matrix_ * v4;
    }
    
    template <typename T>
    vect<T> TransformMatrix<T>::getLeft(){
        constexpr auto v4 = glm::vec4(IMovable<T>::worldLeft, 0);
        return matrix_ * v4;
    }
    
    template <typename T>
    vect<T> TransformMatrix<T>::getRight(){
        constexpr auto v4 = glm::vec4(IMovable<T>::worldRight, 0);
        return matrix_ * v4;
    }
    
    template <typename T>
    vect<T> TransformMatrix<T>::getDown(){
        constexpr auto v4 = glm::vec4(IMovable<T>::worldDown, 0);
        return matrix_ * v4;
    }
    
    template <typename T>
    vect<T> TransformMatrix<T>::getUp(){
        constexpr auto v4 = glm::vec4(IMovable<T>::worldUp, 0);
        return matrix_ * v4;
    }
    
    template <typename T>
    vect<T> TransformMatrix<T>::getPosition(){
        return matrix_[3];
    }
    
    template <typename T>
    vect<T> TransformMatrix<T>::getScale(){
        return vect<T>(matrix_[0][0], matrix_[1][1], matrix_[2][2]);
    }
    
    template <typename T>
    matr<T>& TransformMatrix<T>::getMatrix(){
        return matrix_;
    }
    
    template <typename T>
    void TransformMatrix<T>::setPosition        (const vect<T>& pos){
        //matrix_ = glm::translate<T,glm::defaultp>(glm::identity<matr<T>>(), pos);
        matrix_[3].x = pos.x;
        matrix_[3].y = pos.y;
        matrix_[3].z = pos.z;
    }
    
    template <typename T>
    void TransformMatrix<T>::setPosition        (T x, T y, T z){
        //matrix_ = glm::translate<T,glm::defaultp>(matrix_, vect<T>(x,y,z));
        setPosition(vect<T>(x,y,z));
    }
    
    // TODO Make fast calculations!
    template <typename T>
    void TransformMatrix<T>::setScale           (const vect<T>& scale){
		matrix_ = glm::scale(matrix_, scale);
    }
    
    template <typename T>
    void TransformMatrix<T>::setScale           (T x, T y, T z){
		setScale(vect<T>(x,y,z));
    }
    
    template <typename T>
    void TransformMatrix<T>::setRotation        (const quater<T>& qrot){
        matrix_ = glm::toMat4(qrot);
    }
    
    template <typename T>
    void TransformMatrix<T>::setRotation        (T rx, T ry, T rz){
        matrix_ = glm::toMat4(quater<T>(vect<T>(rx,ry,rz)));
    }
    
    template <typename T>
    void TransformMatrix<T>::moveUp             (T u){
        matrix_ = glm::translate(matrix_, u * IMovable<T>::worldUp);
    }
    
    template <typename T>
    void TransformMatrix<T>::moveDown           (T u){
        matrix_ = glm::translate(matrix_, u * IMovable<T>::worldDown);
    }
    
    template <typename T>
    void TransformMatrix<T>::moveLeft           (T u){
        matrix_ = glm::translate(matrix_, u * IMovable<T>::worldLeft);
    }
    
    template <typename T>
    void TransformMatrix<T>::moveRight          (T u){
        matrix_ = glm::translate(matrix_, u * IMovable<T>::worldRight);
    }
    
    template <typename T>
    void TransformMatrix<T>::moveForward        (T u){
        matrix_ = glm::translate(matrix_, u * IMovable<T>::worldForward);
    }
    
    template <typename T>
    void TransformMatrix<T>::moveBackward       (T u){
        matrix_ = glm::translate(matrix_, u * IMovable<T>::worldBackward);
    }
    
    template <typename T>
    void TransformMatrix<T>::rotatePitchUp      (T u){
        matrix_ = glm::rotate(matrix_,u,IMovable<T>::worldRight);
    }
    
    template <typename T>
    void TransformMatrix<T>::rotatePitchDown    (T u){
        matrix_ = glm::rotate(matrix_,u,IMovable<T>::worldLeft);
    }
    
    template <typename T>
    void TransformMatrix<T>::rotateYawLeft      (T u){
        matrix_ = glm::rotate(matrix_,u,IMovable<T>::worldUp);
    }
    
    template <typename T>
    void TransformMatrix<T>::rotateYawRight     (T u){
        matrix_ = glm::rotate(matrix_,u,IMovable<T>::worldDown);
    }
    
    template <typename T>
    void TransformMatrix<T>::rotateRollLeft     (T u){
        matrix_ = glm::rotate(matrix_,u,IMovable<T>::worldBackward);
    }
    
    template <typename T>
    void TransformMatrix<T>::rotateRollRight    (T u){
        matrix_ = glm::rotate(matrix_,u,IMovable<T>::worldForward);    
    }
}