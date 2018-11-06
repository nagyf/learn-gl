#version 330 core
in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;
out vec4 fragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main() {
    // Ambient
    float specularStrength = 0.5;
    float ambientStrength = 0.1;
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;
    
    // Diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * texture(material.diffuse, texCoords).rgb;
    
    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;
    
    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}
