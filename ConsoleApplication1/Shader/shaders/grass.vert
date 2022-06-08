#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec2 texCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform float time;
uniform float random;
uniform float intensity;

void main()
{

    vec4 position =projection * view * model *  vec4(pos, 1.0);
    
    vec3 offset = vec3( intensity * (cos( time/1.5 )  * (1.0 - tex.y)) * sin( pos.x + random ),
                           0.25 * sin( 1.5*pos.x + 2.0*pos.z ) * (1.0 - tex.x),
                          intensity * (cos( time/2.0 ) * (1.0 - tex.x)) * sin( pos.z + 2.0*random)
                         );


    position.x += offset.x/10.5;
    //position.y += (offset.x + offset.y)/3.5;
    //position.z += offset.z;



    gl_Position = position;
    texCoord = tex;

    Normal = mat3(transpose(inverse(model))) * norm;
	FragPos = (model * vec4(pos, 1.0)).xyz;
}

