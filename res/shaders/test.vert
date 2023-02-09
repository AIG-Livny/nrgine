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

//out mat4 mat_Model;
//out mat4 mat_Projection;
//out mat4 mat_View;

void main(){
   mat4 mvp    = mProjection * mView * mModel;
   //Normal      = vec3(mModel * vec4(v_nor, 1.0));
   Normal      = v_nor;
   FragPos     = vec3(mModel * vec4(v_pos, 1.0));
   //FragPos     = vec3(mvp * vec4(v_pos, 1.0));
   TexCoords   = v_tex;
   //gl_Position = mvp * vec4(v_pos,1);

   //FragPos = vec3(mModel * vec4(v_pos, 1.0));
   //Normal.x = v_nor.z;
   //Normal.y = v_nor.y;
   //Normal.z = v_nor.z;
   //Normal = v_nor;
   //Normal = mat3(transpose(inverse(mModel))) * v_nor; 
   gl_Position = mProjection * mView * vec4(FragPos, 1.0);
}