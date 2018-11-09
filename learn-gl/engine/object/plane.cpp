//
//  plane.cpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 07..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include "plane.hpp"
#include "../data/vertex.hpp"
#include "../data/texture.hpp"

Plane::Plane(const float size, const std::vector<Texture> &textures) {
    float halfSize = size / 2.0f;
    // Vertexes and normals
    float vertex_data[288] = {
        // positions                 // normals           // texture coords
        -halfSize,  halfSize, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         halfSize,  halfSize, 0.0f,  0.0f,  0.0f, -1.0f,  100.0f,  0.0f,
         halfSize, -halfSize, 0.0f,  0.0f,  0.0f, -1.0f,  100.0f,  100.0f,
        -halfSize, -halfSize, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  100.0f
    };
    
    float indices[] = {
        0, 3, 2,
        2, 1, 0
    };
    
    std::vector<Vertex> vertices;
    for(int i = 0; i < sizeof(vertex_data)/sizeof(float); i+=8) {
        Vertex v;
        v.position = glm::vec3(vertex_data[i], vertex_data[i + 1], vertex_data[i + 2]);
        v.normal = glm::vec3(vertex_data[i + 3], vertex_data[i + 4], vertex_data[i + 5]);
        v.texCoords = glm::vec2(vertex_data[i + 6], vertex_data[i + 7]);
        vertices.push_back(v);
    }
    
    mesh.reset(new Mesh(vertices, std::vector<unsigned int>(indices, indices + sizeof(indices) / sizeof(unsigned int)), textures));
    mesh->setParent(this);
}

Plane::~Plane() {
}

void Plane::doRender(const Shader &shader) {
    mesh->render(shader);
}
