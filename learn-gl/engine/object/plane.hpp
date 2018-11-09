//
//  plane.hpp
//  learn-gl
//
//  Created by Ferenc Nagy on 2018. 11. 07..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef plane_hpp
#define plane_hpp

#include <vector>
#include <boost/scoped_ptr.hpp>
#include "gl-object.hpp"
#include "mesh.hpp"
#include "../data/texture.hpp"

class Plane: public GLObject {
protected:
    boost::scoped_ptr<Mesh> mesh;
    virtual void doRender(const Shader &shader);
public:
    Plane(const float size, const std::vector<Texture> &textures);
    virtual ~Plane();
};

#endif /* plane_hpp */
