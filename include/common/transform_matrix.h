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
        vect<T> scale_;
        quater<T> rotation_;
        vect<T> position_;
        
        inline void matrixUpdate();
        
    public:
        TransformMatrix()
        :
        matrix_(glm::identity<matr<T>>())
        {}
        
        [[nodiscard]]       inline vect<T>    getBackward ();
        [[nodiscard]]       inline vect<T>    getForward  ();
        [[nodiscard]]       inline vect<T>    getLeft     ();
        [[nodiscard]]       inline vect<T>    getRight    ();
        [[nodiscard]]       inline vect<T>    getDown     ();
        [[nodiscard]]       inline vect<T>    getUp       ();
        
        [[nodiscard]]       inline vect<T>    getPitch    ();
        [[nodiscard]]       inline vect<T>    getYaw      ();
        [[nodiscard]]       inline vect<T>    getRoll     ();
        [[nodiscard]] const inline vect<T>&   getScale    ();
        [[nodiscard]] const inline quater<T>& getRotation ();
        [[nodiscard]] const inline vect<T>&   getPosition ();
        [[nodiscard]]       inline matr<T>&   getMatrix   ();

        inline void setPosition (const vect<T>& pos);
        inline void setPosition (T x, T y, T z);
        inline void setScale    (const vect<T>& scale);
        inline void setScale    (T x, T y, T z);
        inline void setRotation (const quater<T>& qrot);
        inline void setRotation (T rx, T ry, T rz);

        inline void move        (vect<T> v);
        inline void rotate      (quater<T> qrot);
        inline void scale       (vect<T> v);
};

template <typename T>
void TransformMatrix<T>::matrixUpdate(){
    matrix_[0]      = vect4<T>(0);
    matrix_[1]      = vect4<T>(0);
    matrix_[2]      = vect4<T>(0);
    matrix_[0].x    = scale_.x;
    matrix_[1].y    = scale_.y;
    matrix_[2].z    = scale_.z;
    matrix_[3].x    = position_.x;
    matrix_[3].y    = position_.y;
    matrix_[3].z    = position_.z;
    matrix_[3].w    = 1;
	matrix_         = glm::toMat4(rotation_) * matrix_;
}

template <typename T>
vect<T> TransformMatrix<T>::getBackward(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldBackward, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getForward(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldForward, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getLeft(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldLeft, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getRight(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldRight, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getDown(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldDown, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getUp(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldUp, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getPitch(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldPitch, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getYaw(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldYaw, 0);
    return rotation_ * v4;
}

template <typename T>
vect<T> TransformMatrix<T>::getRoll(){
    constexpr auto v4 = vect4<T>(IMovable<T>::worldRoll, 0);
    return rotation_ * v4;
}

template <typename T>
const vect<T>& TransformMatrix<T>::getScale(){
    return scale_;
}

template <typename T>
const quater<T>& TransformMatrix<T>::getRotation(){
    return rotation_;
}

template <typename T>
const vect<T>& TransformMatrix<T>::getPosition(){
    return position_;
}

template <typename T>
matr<T>& TransformMatrix<T>::getMatrix(){
    return matrix_;
}

template <typename T>
void TransformMatrix<T>::setPosition      (const vect<T>& pos){
    matrix_[3].x = pos.x;
    matrix_[3].y = pos.y;
    matrix_[3].z = pos.z;
}

template <typename T>
void TransformMatrix<T>::setPosition        (T x, T y, T z){
    matrix_[3].x = x;
    matrix_[3].y = y;
    matrix_[3].z = z;
}

template <typename T>
void TransformMatrix<T>::setScale           (const vect<T>& scale){
    scale_ = scale;
    matrixUpdate();
}

template <typename T>
void TransformMatrix<T>::setScale           (T x, T y, T z){
	setScale(vect<T>(x,y,z));
}

template <typename T>
void TransformMatrix<T>::setRotation        (const quater<T>& qrot){
    rotation_ = qrot;
    matrixUpdate();
}

template <typename T>
void TransformMatrix<T>::setRotation        (T rx, T ry, T rz){
    setRotation(quater<T>(vect<T>(rx, ry, rz)));
}

template <typename T>
void TransformMatrix<T>::move(vect<T> v){
    matrix_[3].x += v.x;
    matrix_[3].y += v.y;
    matrix_[3].z += v.z;
}
template <typename T>
void TransformMatrix<T>::rotate(quater<T> qrot){
    matrix_ = glm::toMat4(qrot) * matrix_;
}

template <typename T>
void TransformMatrix<T>::scale(vect<T> v){
    matrix_[0] *= v[0];
	matrix_[1] *= v[1];
	matrix_[2] *= v[2];
}

} // namespace common