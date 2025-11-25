#version 450

layout(location = 0) in vec3 vNormal;

//layout(location = 2) in vec3 vPosition;



layout(location = 0) out vec4 fragColor;

// const vec3 light_direction= normalize(vec3(0.5, 1.0, 0.3));
// const vec3 light_color=vec3(1.0);

void main()
{
    // vec3 n= normalize(vNormal);
    // float diffuse= max(dot(n, light_direction), 0.0);

    //fragColor = vec4(diffuse*light_color, 1.0);
    fragColor=vec4(vNormal,1.0);
}
