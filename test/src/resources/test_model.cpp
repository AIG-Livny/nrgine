#include <gtest/gtest.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include "resources/model.h"


class TestModel : public testing::Test{
    public:
        inline static GLFWwindow* window;
        
        static void SetUpTestSuite() {
            glfwInit();
            window = glfwCreateWindow(10, 10, "TEST", NULL, NULL);
            glfwMakeContextCurrent(window);
            glewExperimental = GL_TRUE;
            glewInit();    
        }
    
        static void TearDownTestSuite() {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
};

TEST_F(TestModel, Not_load_empty_or_missing_path){
    ASSERT_ANY_THROW(resources::Model a(""));
}

TEST_F(TestModel, Not_load_bad_model){
    ASSERT_ANY_THROW(resources::Model a("test/res/tex.png"));
}

TEST_F(TestModel, Preload) {
    ASSERT_NO_THROW(resources::Model a("test/res/box.obj"));
    resources::Model m("test/res/box.obj");
    ASSERT_EQ(m.getLoadState(), common::IResource::LoadState::NotLoaded);
    m.setPreloaded();
    ASSERT_EQ(m.getLoadState(), common::IResource::LoadState::PreLoaded);
    ASSERT_NE(m.getMeshes().size(),0);
    for(const auto& mesh : m.getMeshes()){
        ASSERT_NE(mesh.vertices.size(), 0);
    }
}

TEST_F(TestModel, Load) {
    resources::Model m("test/res/box.obj");
    m.setLoaded();
    ASSERT_EQ(m.getLoadState(), common::IResource::LoadState::Loaded);
    ASSERT_NE(m.getMeshes().size(),0);
    for(const auto& mesh : m.getMeshes()){
        ASSERT_NE(mesh.vertexArrayObject, 0);
    }
}

TEST_F(TestModel, Resume_from_Loaded_to_preloaded_state) {
    resources::Model m("test/res/box.obj");
    m.setLoaded();
    m.setPreloaded();
    ASSERT_NE(m.getMeshes().size(),0);
    for(const auto& mesh : m.getMeshes()){
        ASSERT_NE(mesh.vertices.size(), 0);
        ASSERT_EQ(mesh.vertexArrayObject, 0);
    }
}

TEST_F(TestModel, Unload) {
    resources::Model m("test/res/box.obj");
    m.setLoaded();
    ASSERT_EQ(m.getLoadState(), common::IResource::LoadState::Loaded);
    ASSERT_NE(m.getMeshes().size(),0);
    m.setUnloaded();
    ASSERT_EQ(m.getLoadState(), common::IResource::LoadState::NotLoaded);
    ASSERT_EQ(m.getMeshes().size(),0);
}