#version 450

layout(location = 0) in vec3 vNormal;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vPosition;


layout(location = 0) out vec4 fragColor;

layout(set = 1, binding = 0) uniform sampler2D textureSampler;

const vec3 light_direction= normalize(vec3(1.0, -0.2, 0.0));
const vec3 light_color=vec3(1.0);

void main()
{
    vec3 n= normalize(vNormal);
    float diffuse= max(dot(n, light_direction), 0.0);
    vec3 texColor =texture(textureSampler, vTexCoord).rgb;
    fragColor = vec4(diffuse*light_color*texColor + vec3(0.3)*texColor, 1.0);
    // fragColor=vec4(vNormal,1.0);

}
