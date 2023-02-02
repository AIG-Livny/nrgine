#version 300 es        

precision mediump float;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

//in mat4 mat_Model;
//in mat4 mat_Projection;
//in mat4 mat_View;

out vec4 FragColor;    

uniform vec3 viewPos;
uniform vec3 lightPos;

vec3 lightColor         = vec3(0.9,0.9,0.5);
vec3 objectColor        = vec3(0.9,0.5,0.5);

void main() {
    
    // ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightDir = normalize(FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;
    //FragColor = vec4(result, 1.0);
    FragColor = vec4(objectColor * norm, 1.0);
}