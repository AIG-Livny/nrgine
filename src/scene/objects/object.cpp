#include "scene/objects/object.h"

#include "scene/node.h"

namespace scene::objects{

// IMovable
      glm::vec3  Object::getBackward  ()                   const     {return getParent()->getBackward();}
      glm::vec3  Object::getForward   ()                   const     {return getParent()->getForward ();}
      glm::vec3  Object::getLeft      ()                   const     {return getParent()->getLeft    ();}
      glm::vec3  Object::getRight     ()                   const     {return getParent()->getRight   ();}
      glm::vec3  Object::getDown      ()                   const     {return getParent()->getDown    ();}
      glm::vec3  Object::getUp        ()                   const     {return getParent()->getUp      ();}
      glm::vec3  Object::getPitch     ()                   const     {return getParent()->getPitch   ();}
      glm::vec3  Object::getYaw       ()                   const     {return getParent()->getPitch   ();}
      glm::vec3  Object::getRoll      ()                   const     {return getParent()->getRoll    ();}
const glm::vec3& Object::getScale     ()                   const     {return getParent()->getScale();}
const glm::quat& Object::getRotation  ()                   const     {return getParent()->getRotation();}
const glm::vec3& Object::getPosition  ()                   const     {return getParent()->getPosition();}
      glm::mat4& Object::getMatrix    ()                             {return getParent()->getMatrix();}
      void       Object::setPosition  (const glm::vec3& pos)         {getParent()->setPosition(pos);}
      void       Object::setPosition  (float x, float y, float z)    {getParent()->setPosition(x,y,z);}
      void       Object::setScale     (const glm::vec3& scale)       {getParent()->setScale(scale);}
      void       Object::setScale     (float x, float y, float z)    {getParent()->setScale(x,y,z);}
      void       Object::setRotation  (const glm::quat& qrot)        {getParent()->setRotation(qrot);}
      void       Object::setRotation  (float rx, float ry, float rz) {getParent()->setRotation(rx,ry,rz);}
      void       Object::move         (glm::vec3 v)                  {getParent()->move(v);}
      void       Object::rotate       (glm::quat qrot)               {getParent()->rotate(qrot);}    
      void       Object::scale        (glm::vec3 v)                  {getParent()->scale(v);}

} // namespace scene::objects