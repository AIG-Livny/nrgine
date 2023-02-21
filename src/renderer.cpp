#include "renderer.h"

#include <GL/glew.h>

#include "scene/scene.h"
#include "scene/objects/object.h"
#include "scene/objects/model.h"
#include "scene/objects/camera.h"
#include "resources/shader.h"

void Renderer::Render(scene::Scene* scene) {
    for(auto* o : scene->getObjects(scene::objects::Model)){
        auto* mod = static_cast<scene::objects::TModel*>(o);
        auto* cam = static_cast<scene::objects::TCamera*>(scene->getObjects(scene::objects::Camera).front());
        auto& lp = scene->getObjects(scene::objects::Light).back()->getParent()->getPosition();
        
        glUseProgram(mod->getShader()->getHandler());
        mod->getShader()->setMat4("mModel",         mod->getMatrix());
        mod->getShader()->setMat4("mView",          cam->getView());
        mod->getShader()->setMat4("mProjection",    cam->getProjection());
        mod->getShader()->setVec3("lightPos",       lp);
        
        for(auto& mesh : mod->getModel()->getMeshes()){   
            glBindVertexArray(mesh.vertexArrayObject);
            glDrawElements(GL_TRIANGLES, mesh.indices_num, GL_UNSIGNED_INT, 0);
        }
    }
}