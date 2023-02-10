#include <gtest/gtest.h>

#include "resources/manager.h"

TEST(resources_manager, Add_model){
    resources::Manager man;
    man.addModel("test/res/box.obj");
    auto mod = man.findModel("test/res/box.obj");
    ASSERT_NE(mod, nullptr);
    ASSERT_EQ(mod->getLoadState(), resources::Resource::LoadState::NotLoaded);
}

TEST(resources_manager, Add_shader){
    resources::Manager man;
    man.addShader("test/res/shader");
    auto sh = man.findShader("test/res/shader");
    ASSERT_NE(sh, nullptr);
    ASSERT_EQ(sh->getLoadState(), resources::Resource::LoadState::NotLoaded);
}
