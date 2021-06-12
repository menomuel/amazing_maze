#include "texture.h"


std::shared_ptr<QOpenGLTexture> Texture::loadTexture(const std::string &file)
{
    auto tex = std::make_shared<QOpenGLTexture>(QImage(file.c_str()));
    tex->setMinificationFilter(QOpenGLTexture::Nearest);
    tex->setMagnificationFilter(QOpenGLTexture::Linear);
    tex->setWrapMode(QOpenGLTexture::Repeat);
    tex->setMinMagFilters(QOpenGLTexture::LinearMipMapLinear, QOpenGLTexture::LinearMipMapLinear);
    tex->setMaximumAnisotropy(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);
    return tex;
}
