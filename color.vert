#version 450
//#extension GL_ARB_separate_shader_objects: enable

layout(location = 0) in vec3 position; //x,y,z
layout(location = 1) in vec3 normal; //r,g,b

layout(location = 0) out vec3 vNormal;
// layout(location = 2) out vec3 vPosition; //light?

layout(push_constant) uniform mod {
    mat4 model;
} model;

layout(set = 0, binding = 0) uniform cam {
    mat4 view;
    mat4 projection;
} camera;

// layout(set = 1, binding = 0) uniform lght {
//     vec3 direction;
//     vec3 color;
// } light;


out gl_PerVertex { vec4 gl_Position;};


//gl_.enable(0x8642);
void main()
{
    // vec4 world= model.model * vec4(position, 1.0);
    // vNormal = mat3(model.model)*normal; //model is vec 4, so we need vector 3
    // vPosition=world.xyz;
    vNormal=normal;
    gl_Position =   camera.projection * camera.view * model.model * vec4(position, 1.0);
   // gl_PointSize=position.z;
}


