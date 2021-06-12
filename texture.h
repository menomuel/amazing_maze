#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLShaderProgram>
#include <string>
#include <QOpenGLTexture>
#include <memory>

class Texture
{
public:
    static std::shared_ptr<QOpenGLTexture> loadTexture(const std::string& file);
};

#endif // TEXTURE_H
