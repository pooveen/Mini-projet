#include "Renderer.hpp"
#include "utils.hpp"

Renderer::Renderer(const Mesh& mesh, const Shader& shader)
    : shader(shader){
    setupMesh(mesh);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::draw() const{
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::setupMesh(const Mesh& mesh){
    // Générer VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // VBO pour sommets (positions)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(glm::vec3), 
                 mesh.getVertices().data(), GL_STATIC_DRAW);

    // EBO pour indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndices().size() * sizeof(unsigned int),
                 mesh.getIndices().data(), GL_STATIC_DRAW);

    // Attribut position (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindVertexArray(0); // débind VAO
}
