#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

layout(location = 0) out vec3 vNormal;
layout(location = 1) out vec2 vTexCoord;
layout(location = 2) out vec3 vPosition;

layout(push_constant) uniform mod {
    mat4 model;
} model;

layout(set = 0, binding = 0) uniform cam {
    mat4 view;
    mat4 projection;
} camera;

out gl_PerVertex { vec4 gl_Position; };

void main()
{
    vec4 world= model.model * vec4(position, 1.0);
    vNormal = mat3(model.model)*normal; //model is vec 4, so we need vector 3
    vPosition=world.xyz;
    // vNormal=normal;

   // gl_PointSize=position.z;
    // vColor = color;
    vTexCoord = texcoord;
    gl_Position =   camera.projection * camera.view * model.model * vec4(position, 1.0);
}

