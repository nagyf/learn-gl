//
//  skybox.hpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 09..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef skybox_hpp
#define skybox_hpp

#include "gl-object.hpp"
#include "../data/texture.hpp"

class Skybox: public GLObject {
private:
    unsigned int VAO, VBO;
    Texture cubemapTexture;
protected:
    virtual void doRender(const Shader &shader);
public:
    Skybox(Texture cubemapTexture);
    ~Skybox();
};

#endif /* skybox_hpp */
