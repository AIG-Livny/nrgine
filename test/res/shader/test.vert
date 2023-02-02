#version 300 es            

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_nor;
layout(location = 2) in vec2 v_tex;

uniform mat4 mModel;
uniform mat4 mProjection;
uniform mat4 mView;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main(){
   mat4 mvp    = mProjection * mView * mModel;
   Normal      = v_nor;
   FragPos     = vec3(mModel * vec4(v_pos, 1.0));
   TexCoords   = v_tex;
   gl_Position = mvp * vec4(v_pos,1);
}