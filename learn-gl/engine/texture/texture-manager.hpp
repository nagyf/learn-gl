//
//  texture-manager.hpp
//  hello-gl2
//
//  Created by Ferenc Nagy on 2018. 11. 05..
//  Copyright © 2018. Ferenc Nagy. All rights reserved.
//

#ifndef texture_manager_hpp
#define texture_manager_hpp

#include <vector>
#include <string>
#include "../data/texture.hpp"

class TextureManager {
public:
    TextureManager();
    
    Texture load(const std::string &type, const std::string &path) const;
    
    Texture loadCubemap(const std::vector<std::string> &faces) const;
};

#endif /* texture_manager_hpp */
