#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <GLFW/glfw3.h> 

#include "interfaces/IApplication.h"

namespace reactphysics3d{ class PhysicsCommon;}
namespace resources{ class Manager;}
namespace scene{ class Scene;}

class ApplicationMock : public IApplication{
public:
    MOCK_METHOD(std::unique_ptr<reactphysics3d::PhysicsCommon>&,    getPhysicsCommon, (), (override) );
    MOCK_METHOD(std::unique_ptr<resources::Manager>&,               getResourceManager, (), (override));
    MOCK_METHOD(std::unique_ptr<scene::Scene>&,                     getCurrentScene, (), (override));
    MOCK_METHOD(GLFWwindow*,                                        getGLFWWindow, (), (override));
    MOCK_METHOD(void,                                               mouseMoveEvent, (double,double), (override));
    MOCK_METHOD(void,                                               keyPressEvent, (int,int,int,int), (override));
    MOCK_METHOD(void,                                               run, (), (override));
    
};
