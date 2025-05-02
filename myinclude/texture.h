#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb/stb_image.h"

class Texture {

    unsigned int ID;
    GLenum texture, target;

    public:
        Texture(const char* filePath, GLenum target, GLenum texture, GLint internalFormat, GLenum format);
        void use();
    };

#endif