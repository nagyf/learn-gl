//
//  box.cpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 04..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "box.hpp"

Box::Box(const std::vector<Texture> &textures): GLObject() {
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

void Box::doRender(const Shader &shader) {
    mesh->render(shader);
}
