#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include <glad/gl.h>
#include <memory>

class Renderer {
public:
    Renderer(const Mesh& mesh, const Shader& shader);
    ~Renderer();

    void draw() const;

private:
    GLuint VAO, VBO, EBO;
    const Shader& shader;
    std::size_t indexCount;

    void setupMesh(const Mesh& mesh);
};
