#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    normal = mat3(transpose(inverse(model))) * inNormal;  
    fragPos = vec3(model * vec4(position, 1.0));
    texCoords = inTexCoords;
}
