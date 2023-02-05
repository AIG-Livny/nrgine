#include "resources/shader.h"

#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

namespace resources{
    Shader::Shader(const std::filesystem::path& path) : Resource(path){
        if(std::filesystem::exists(path) != true){
            throw std::runtime_error("SHADER::Missing file");
        }
    }
    
    void Shader::loadToRAM(){
        using namespace std;
        using namespace std::filesystem;

        auto find_any = [](const path& p, const string& ext)->path{
            if(exists(p) && is_directory(p)){
                for(auto const& e : recursive_directory_iterator(p)){
                    if(is_regular_file(e)){
                        auto fext = e.path().extension();
                        if(ext == fext){
                            return e; 
                        }
                    }
                }
            }
            return path("");
        };
    
        auto vertex_path    = find_any(getPath(),".vert");
        auto fragment_path  = find_any(getPath(),".frag");
        auto geometry_path  = find_any(getPath(),".geom");
    
        if(vertex_path.empty()){
            throw std::runtime_error("SHADER::Not found vertex shader");
        }

        auto open_shader = [](const path& p, std::unique_ptr<string>& strout)->void{
            if(p.empty()){
                return;
            }
            ifstream shader_file;
            shader_file.exceptions(ifstream::failbit | ifstream::badbit);
            try{
                shader_file.open(p);
                strout = make_unique<string>(istreambuf_iterator<char>(shader_file), istreambuf_iterator<char>());
            }catch (ifstream::failure& e){
                throw runtime_error("SHADER::File not succesfully read");
            }
        };
    
        vertexShader_   = make_unique<string>();
        fragmentShader_ = make_unique<string>();
        geometryShader_ = make_unique<string>();
    
        open_shader(vertex_path,vertexShader_);
        open_shader(fragment_path,fragmentShader_);
        open_shader(geometry_path,geometryShader_);
    }
    
    void Shader::loadToGPU(){
        using namespace std;
    
        auto check_compile_errors = [](){};
    
        unsigned int vertex;
        unsigned int fragment;
        unsigned int geometry;
        GLint success;
        GLchar info_log[1024];
    
        const char* cc = vertexShader_->c_str();
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &cc, 0);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vertex, 1024, NULL, info_log);
            ostringstream strout;
            strout << "ERROR::SHADER_COMPILATION_ERROR of type: VERTEX\n" << info_log << "\n" << std::endl;
            throw runtime_error(strout.str());
        }
        
        if(fragmentShader_->empty() == false){
            const char* cc = fragmentShader_->c_str();
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &cc, 0);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(fragment, 1024, NULL, info_log);
                ostringstream strout;
                strout << "ERROR::SHADER_COMPILATION_ERROR of type: FRAGMENT\n" << info_log << "\n" << std::endl;
                throw runtime_error(strout.str());
            }
        }
        
        if(geometryShader_->empty() == false){
            const char* cc = geometryShader_->c_str();
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &cc, NULL);
            glCompileShader(geometry);
   
            glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
            if(!success){
                glGetShaderInfoLog(geometry, 1024, NULL, info_log);
                ostringstream strout;
                strout << "ERROR::SHADER_COMPILATION_ERROR of type: GEOMETRY\n" << info_log << "\n" << std::endl;
                throw runtime_error(strout.str());
            }
        }
        
        handlerGPU_ = glCreateProgram();
        glAttachShader(handlerGPU_, vertex);
        if(fragmentShader_->empty() == false){
            glAttachShader(handlerGPU_, fragment);
        }
        if(geometryShader_->empty() == false){
            glAttachShader(handlerGPU_, geometry);
        }
        glLinkProgram(handlerGPU_);
        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(handlerGPU_, 1024, NULL, info_log);
            ostringstream strout;
            strout << "ERROR::SHADER_COMPILATION_ERROR of type: LINK\n" << info_log << "\n" << std::endl;
            throw runtime_error(strout.str());
            handlerGPU_ = 0;
        }
        
        glDeleteShader(vertex);
        if(fragmentShader_->empty() == false){
            glDeleteShader(fragment);
        }
        if(geometryShader_->empty() == false){
            glDeleteShader(geometry);
        }
    }
    
    void Shader::setLoaded(){
        if(loadState == LoadState::Loaded){
            return;
        }
        if(loadState == LoadState::NotLoaded){
            setPreloaded();
        }
        if(loadState == LoadState::PreLoaded){
            loadToGPU();
        }
        
        loadState = LoadState::Loaded;
    }
    
    void Shader::setPreloaded(){
        if(loadState == LoadState::PreLoaded){
            return;
        }
        if(loadState == LoadState::NotLoaded){
            loadToRAM();
        }
        if(loadState == LoadState::Loaded){
            if(handlerGPU_){
                glDeleteProgram(handlerGPU_);
                handlerGPU_ = 0;
            }
        }
               
        loadState = LoadState::PreLoaded;
    }
    
    void Shader::setUnloaded(){
        if(loadState == LoadState::NotLoaded){
            return;
        }
        if(loadState == LoadState::Loaded){
            setPreloaded();
        }
        if(loadState == LoadState::PreLoaded){
            vertexShader_   = std::make_unique<std::string>();
            fragmentShader_ = std::make_unique<std::string>();
            geometryShader_ = std::make_unique<std::string>();
        }
               
        loadState = LoadState::NotLoaded;
    }
}