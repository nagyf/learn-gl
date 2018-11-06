//
//  mesh.hpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 05..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <vector>
#include "../data/texture.hpp"
#include "../data/vertex.hpp"
#include "gl-object.hpp"

class Mesh: public GLObject {
protected:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO, VBO, EBO;
    
    void setupMesh();
    virtual void doRender(const Shader &shader);
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
};

#endif /* mesh_hpp */
