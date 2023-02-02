#pragma once

#include <memory>

template <typename T>
using pu = std::unique_ptr<T>;

template <typename T>
using ps = std::shared_ptr<T>;

namespace resources{
    class Resource;
    class Manager;
    class Model;
    class Shader;
    class Texture;
};

namespace reactphysics3d{
    class PhysicsCommon;
    class PhysicsWorld;
};

namespace scene{
    class Scene;
    class Node;
}

struct GLFWwindow;
class Application;
class Renderer;