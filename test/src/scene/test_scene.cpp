#include <gtest/gtest.h>

#include "application.h"
#include "scene/scene.h"

class TestScene : public testing::Test{
    inline static Application* app;
    public:
        static void SetUpTestSuite() {
            app = new Application();    
        }
    
        static void TearDownTestSuite() {
            delete app;
        }
};


//TEST_F(TestScene, scene){  
//}
