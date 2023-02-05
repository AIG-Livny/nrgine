#include <gtest/gtest.h>

#include "resources/shader.h"

TEST(resources_shader, Not_load_missing_path){
    ASSERT_ANY_THROW(resources::Shader s("MISSING"));
}

TEST(resources_shader, Preload){
    ASSERT_NO_THROW(resources::Shader e("test/res/shader"));
    resources::Shader s("test/res/shader");
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::NotLoaded);
    s.setPreloaded();
    ASSERT_FALSE(s.getVertexShader().empty());
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::PreLoaded);
}

TEST(resources_shader, Load){
    ASSERT_NO_THROW(resources::Shader e("test/res/shader"));
    resources::Shader s("test/res/shader");
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::NotLoaded);
    ASSERT_EQ(s.getHandler(), 0);
    ASSERT_TRUE(s.getVertexShader().empty());
    s.setLoaded();
    ASSERT_FALSE(s.getVertexShader().empty());
    ASSERT_NE(s.getHandler(), 0);
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::Loaded);
}

TEST(resources_shader, Unload){
    resources::Shader s("test/res/shader");
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::NotLoaded);
    ASSERT_EQ(s.getHandler(), 0);
    ASSERT_TRUE(s.getVertexShader().empty());
    s.setLoaded();
    ASSERT_FALSE(s.getVertexShader().empty());
    ASSERT_NE(s.getHandler(), 0);
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::Loaded);
    s.setUnloaded();
    ASSERT_TRUE(s.getVertexShader().empty());
    ASSERT_EQ(s.getHandler(), 0);
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::NotLoaded);
}

TEST(resources_shader, Load_from_preloaded){
    resources::Shader s("test/res/shader");
    s.setPreloaded();
    s.setLoaded();
    ASSERT_FALSE(s.getVertexShader().empty());
    ASSERT_NE(s.getHandler(), 0);
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::Loaded);
}

TEST(resources_shader, Unload_from_preloaded){
    resources::Shader s("test/res/shader");
    s.setPreloaded();
    s.setUnloaded();
    ASSERT_TRUE(s.getVertexShader().empty());
    ASSERT_EQ(s.getHandler(), 0);
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::NotLoaded);
}

