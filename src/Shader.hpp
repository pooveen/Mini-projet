#pragma once

#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>

class Shader {
public:
    // Constructeur : charge, compile et link les shaders
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    // Active ce shader
    void use() const;

    // Accès à l'ID du shader (utile si tu veux faire des appels bas niveau)
    GLuint getID() const {return ID;}

    // Fonctions utilitaires pour passer des uniformes
    void setUniform(const std::string& name, const glm::mat4& mat) const;
    void setUniform(const std::string& name, const glm::vec3& vec) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, int value) const;

private:
    GLuint ID;

    // Méthodes internes pour la compilation
    std::string loadFile(const std::string& path) const;
    GLuint compileShader(GLenum type, const std::string& source) const;
    void checkCompileErrors(GLuint shader, const std::string& type) const;
};
