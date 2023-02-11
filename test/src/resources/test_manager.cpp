#include <gtest/gtest.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include "resources/manager.h"

class TestManager : public testing::Test{
    public:
        resources::Manager* man;
        
        void SetUp()    override{
            man = new resources::Manager();    
        };
        void TearDown() override{
            delete man;
        };
};


TEST_F(TestManager, Add_model){
    man->addModel("test/res/box.obj");
    auto mod = man->findModel("test/res/box.obj");
    ASSERT_NE(mod, nullptr);
    ASSERT_EQ(mod->getLoadState(), resources::Resource::LoadState::NotLoaded);
}

TEST_F(TestManager, Add_shader){
    man->addShader("test/res/shader");
    auto sh = man->findShader("test/res/shader");
    ASSERT_NE(sh, nullptr);
    ASSERT_EQ(sh->getLoadState(), resources::Resource::LoadState::NotLoaded);
}
