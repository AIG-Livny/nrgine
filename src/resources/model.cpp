#include "resources/model.h"

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <functional>
#include <filesystem>

auto* openFile(Assimp::Importer& ai, const std::filesystem::path& path){
    std::vector<std::string> exts = {".obj"};
    if(std::find(exts.begin(), exts.end(), path.extension().string()) == exts.end()){
        throw std::runtime_error("Not supported extension");
    }
    auto* scene = ai.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error(ai.GetErrorString());
    }
    return scene;
}


namespace resources{
    Model::Model(const std::filesystem::path& path)
    :
    meshes_(std::make_unique<std::vector<Mesh>>(0)),
    Resource(path)
    {
        Assimp::Importer ai;
        openFile(ai,getPath());
    }
    
    
    void Model::loadRAM(){
        Assimp::Importer ai;
        auto* scene = openFile(ai, getPath());
        
        unsigned int mes_num = 0;
        // Recusive calc
        std::function<void(const aiNode*)> recursive_calc;
        recursive_calc = [&mes_num,&recursive_calc](const aiNode* node){
            mes_num += node->mNumMeshes;
            for(unsigned int i = 0; i < node->mNumChildren; i++){
                recursive_calc(node->mChildren[i]);
            }
        };

        recursive_calc(scene->mRootNode);
        meshes_ = std::make_unique<std::vector<Mesh>>(mes_num);
        
        // Recusive parsing
        mes_num = 0;
        std::function<void(const aiNode*)> process_node;
        process_node = [this,&process_node, scene, &mes_num](const aiNode* node){
            for(unsigned int m = 0; m < node->mNumMeshes; m++){
                Mesh* mr = &(meshes_->at(mes_num));
                mes_num += 1;
                aiMesh *mesh = scene->mMeshes[node->mMeshes[m]]; 

                // Making vectors
                mr->vertices = std::make_unique<std::vector<Vertex>>(mesh->mNumVertices);
                unsigned int ind_num = 0;
                for(unsigned int f = 0; f < mesh->mNumFaces; f++){
                    ind_num += mesh->mFaces[f].mNumIndices;
                }
                mr->indices = std::make_unique<std::vector<glm::u32>>(ind_num);

                // Filling vectors
                for(unsigned int v = 0; v < mesh->mNumVertices; v++){
                    Vertex* vtx = &(mr->vertices->at(v));

                    vtx->position = glm::vec3(mesh->mVertices[v].x,mesh->mVertices[v].y,mesh->mVertices[v].z);
                    vtx->normal = glm::vec3(mesh->mNormals[v].x,mesh->mNormals[v].y,mesh->mNormals[v].z);
                    if(mesh->mTextureCoords[0]){
                        vtx->tex_coords = glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
                    }else{
                        vtx->tex_coords = glm::vec2(0.0f, 0.0f);  
                    }
                }

                ind_num = 0;
                for(unsigned int f = 0; f < mesh->mNumFaces; f++){
                    for(unsigned int i = 0; i < mesh->mFaces[f].mNumIndices; i++){
                        mr->indices->at(ind_num) = mesh->mFaces[f].mIndices[i];
                        ind_num += 1;
                    }
                }
            }

            for(unsigned int i = 0; i < node->mNumChildren; i++){
                process_node(node->mChildren[i]);
            }
        };  

        process_node(scene->mRootNode);
    }

    void Model::loadGPU(){
        using namespace glm;
        
        for(auto& m : *meshes_){
            m.indices_num = m.indices->size();
            
            glGenVertexArrays(1, &m.vertexArrayObject);
            glGenBuffers(1, &m.vertexBufferObject);
            glGenBuffers(1, &m.elementBufferObject);
       
            glBindVertexArray(m.vertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, m.vertexBufferObject);
            
            glBufferData(GL_ARRAY_BUFFER, m.vertices->size() * sizeof(Vertex), &m.vertices->at(0), GL_STATIC_DRAW);  
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.elementBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.indices->size() * sizeof(u32), &m.indices->at(0), GL_STATIC_DRAW);
            
            // vertex positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            // vertex normals
            glEnableVertexAttribArray(1);	
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            // vertex texture coords
            glEnableVertexAttribArray(2);	
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);   // unbind VBO
            glBindVertexArray(0);               // unbind VAO
        }
    }

    void Model::unloadGPU(){
        for(auto& m : *meshes_){
            if(m.vertexArrayObject > 0){
                glDeleteVertexArrays(1, &m.vertexArrayObject);
                m.vertexArrayObject = 0;
            }
            if(m.vertexBufferObject > 0){
                glDeleteBuffers(1, &m.vertexBufferObject);
                m.vertexBufferObject = 0;
            }
            if(m.elementBufferObject > 0){
                glDeleteBuffers(1, &m.elementBufferObject);
                m.elementBufferObject = 0;
            }
        }
    }

    void Model::setLoaded(){
        if(loadState == LoadState::Loaded){
            return;
        }
        if(loadState == LoadState::NotLoaded){
            setPreloaded();
        }
        if(loadState == LoadState::PreLoaded){
            loadGPU();
        }
        
        loadState = LoadState::Loaded;
    }

    void Model::setPreloaded(){
        if(loadState == LoadState::PreLoaded){
            return;
        }
        if(loadState == LoadState::NotLoaded){
            loadRAM();
        }
        if(loadState == LoadState::Loaded){
            unloadGPU();
        }
        loadState = LoadState::PreLoaded;
    }
    
    void Model::setUnloaded(){
        if(loadState == LoadState::NotLoaded){
            return;
        }
        if(loadState == LoadState::Loaded){
            setPreloaded();
        }
        if(loadState == LoadState::PreLoaded){
            meshes_ = std::make_unique<std::vector<Mesh>>(0);
        }
        loadState = LoadState::NotLoaded;
    }
}