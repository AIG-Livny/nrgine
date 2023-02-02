#pragma once

#include "common/forwards.h"

namespace scene{
    class Scene{
        private:
            Application* application_;
            reactphysics3d::PhysicsWorld* physicsWorld_;
            pu<Node> rootNode_;

        public:
            Scene(Application* app);
            ~Scene();
            
            [[nodiscard]] inline const auto& getRoot(){return rootNode_;};
            [[nodiscard]] inline const auto& getPhysicsCommon();
            void UpdatePhysics(const float& delta);
    };
}