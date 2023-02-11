#include <gtest/gtest.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include "resources/shader.h"

class TestShader : public testing::Test{
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

TEST_F(TestShader, Not_load_missing_path){
    ASSERT_ANY_THROW(resources::Shader s("MISSING"));
}

TEST_F(TestShader, Preload){
    ASSERT_NO_THROW(resources::Shader e("test/res/shader"));
    resources::Shader s("test/res/shader");
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::NotLoaded);
    s.setPreloaded();
    ASSERT_FALSE(s.getVertexShader().empty());
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::PreLoaded);
}

TEST_F(TestShader, Load){
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

TEST_F(TestShader, Unload){
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

TEST_F(TestShader, Load_from_preloaded){
    resources::Shader s("test/res/shader");
    s.setPreloaded();
    s.setLoaded();
    ASSERT_FALSE(s.getVertexShader().empty());
    ASSERT_NE(s.getHandler(), 0);
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::Loaded);
}

TEST_F(TestShader, Unload_from_preloaded){
    resources::Shader s("test/res/shader");
    s.setPreloaded();
    s.setUnloaded();
    ASSERT_TRUE(s.getVertexShader().empty());
    ASSERT_EQ(s.getHandler(), 0);
    ASSERT_EQ(s.getLoadState(), common::IResource::LoadState::NotLoaded);
}

