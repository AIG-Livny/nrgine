#include <gtest/gtest.h>

#include "application.h"
#include "test/include/application_mock.h"
#include "scene/scene.h"

TEST(scene_node, Add_model){
    ApplicationMock app;
    scene::Scene scn(static_cast<IApplication*>(&app));
    
}
