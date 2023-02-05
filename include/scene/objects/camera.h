#pragma once

#include <glm/glm.hpp>

#include "scene/objects/basic.h"

namespace scene{
    class Node;
} // namespace scene

namespace scene::objects{
    
class Camera:public Basic{
    private:
        glm::mat4 projection_;
        glm::mat4 view_;
    
        float fieldOfView_  = 45.0f;
        float aspect_       = 1;
        float near_         = 0.1f;
        float far_          = 100.0f;

        void calculateProjection(void);
        void calculateView(void);

    public:
	    Camera(Node* parent);

        inline void setFov    (float f);
        inline void setAspect (float f);
        inline void setNear   (float f);
        inline void setFar    (float f);

        [[nodiscard]] inline const glm::mat4& getProjection(void);
        [[nodiscard]] inline const glm::mat4& getView(void);
};

} // namespace scene::objects