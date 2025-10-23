#version 450
//#extension GL_ARB_separate_shader_objects: enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

layout(location = 0) out vec3 vColor;


layout(push_constant) uniform mod {
    mat4 model;
} model;

layout(set = 0, binding = 0) uniform cam {
    mat4 view;
    mat4 projection;
} camera;

out gl_PerVertex { vec4 gl_Position;};


//gl_.enable(0x8642);
void main()
{

    vColor = color;
    gl_Position =   camera.projection * camera.view * model.model * vec4(position, 1.0);
   // gl_PointSize=position.z;
}


