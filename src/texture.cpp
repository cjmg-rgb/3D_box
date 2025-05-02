#include "texture.h"

Texture::Texture(const char* filePath, GLenum target, GLenum texture, GLint internalFormat, GLenum format) 
    : texture(texture), target(target)
{
    glGenTextures(1, &ID);
    glActiveTexture(texture);
    glBindTexture(target, ID);

    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannel;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannel, 0);
    if(data) {
        glTexImage2D(target, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(target);
    };

    stbi_image_free(data);
};

void Texture::use() {
    glActiveTexture(texture);
    glBindTexture(target, ID);
}
