#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "scene/objects/object.h"

namespace scene{
    class Node;
} // namespace scene

namespace scene::objects{
    
class TCamera:public Object{
    private:
        glm::mat4 projection_;
        glm::mat4 view_;
    
        float fieldOfView_  = 45.0f;
        float aspect_       = 1;
        float near_         = 0.1f;
        float far_          = 100.0f;

        inline void calculateProjection(void) {projection_ = glm::perspective(glm::radians(fieldOfView_), aspect_, near_, far_);}

    public:
	    TCamera(Node* parent):
        Object(parent)
        {
            calculateProjection();
        }

        inline void setFov    (float f) {fieldOfView_   = f; calculateProjection();}
        inline void setAspect (float f) {aspect_        = f; calculateProjection();}
        inline void setNear   (float f) {near_          = f; calculateProjection();}
        inline void setFar    (float f) {far_           = f; calculateProjection();}

        [[nodiscard]] inline const glm::mat4& getProjection(void)   {return projection_;}
        [[nodiscard]]        const glm::mat4& getView(void);
        [[nodiscard]] inline Type getType(){return Type::Camera;}
};

} // namespace scene::objects