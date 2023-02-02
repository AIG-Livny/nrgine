#include <gtest/gtest.h>

#include "resources/model.h"

TEST(resources_model, Not_load_empty_or_missing_path){
    ASSERT_ANY_THROW(resources::Model a(""));
}

TEST(resources_model, Not_load_bad_model){
    ASSERT_ANY_THROW(resources::Model a("test/res/tex.png"));
}

TEST(resources_model, Preload) {
    ASSERT_NO_THROW(resources::Model a("test/res/box.obj"));
    resources::Model m("test/res/box.obj");
    ASSERT_EQ(m.getLoadState(), resources::LoadState::NotLoaded);
    m.setPreloaded();
    ASSERT_EQ(m.getLoadState(), resources::LoadState::PreLoaded);
    ASSERT_NE(m.getMeshes().size(),0);
    for(const auto& mesh : m.getMeshes()){
        ASSERT_NE(mesh.vertices->size(), 0);
    }
}

TEST(resources_model, Load) {
    resources::Model m("test/res/box.obj");
    m.setLoaded();
    ASSERT_EQ(m.getLoadState(), resources::LoadState::Loaded);
    ASSERT_NE(m.getMeshes().size(),0);
    for(const auto& mesh : m.getMeshes()){
        ASSERT_NE(mesh.vertexArrayObject, 0);
    }
}

TEST(resources_model, Resume_from_Loaded_to_preloaded_state) {
    resources::Model m("test/res/box.obj");
    m.setLoaded();
    m.setPreloaded();
    ASSERT_NE(m.getMeshes().size(),0);
    for(const auto& mesh : m.getMeshes()){
        ASSERT_NE(mesh.vertices->size(), 0);
        ASSERT_EQ(mesh.vertexArrayObject, 0);
    }
}

TEST(resources_model, Unload) {
    resources::Model m("test/res/box.obj");
    m.setLoaded();
    ASSERT_EQ(m.getLoadState(), resources::LoadState::Loaded);
    ASSERT_NE(m.getMeshes().size(),0);
    m.setUnloaded();
    ASSERT_EQ(m.getLoadState(), resources::LoadState::NotLoaded);
    ASSERT_EQ(m.getMeshes().size(),0);
}