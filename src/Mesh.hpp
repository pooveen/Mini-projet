#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

class Mesh {
public:
    // Constructeur 
    Mesh() = default;
    explicit Mesh(const std::string& filename);

    // Getteur 
    const std::vector<glm::vec3>& getVertices() const {return vertices;}
    const std::vector<glm::vec3>& getNormals() const {return normals;}
    const std::vector<glm::vec3>& getFaceNormals() const {return faceNormals;}
    const std::vector<unsigned int>& getIndices() const {return indices;}

    // init d'un mesh
    bool loadFromOBJ(const std::string& filename);

private:
    std::vector<glm::vec3> vertices;    // Liste des sommets
    std::vector<glm::vec3> normals;     // Normales
    std::vector<glm::vec3> faceNormals; // Normales des faces
    std::vector<unsigned int> indices;  // Indices (faces triangulées)

    // Fonction d'aide pour parser le fichier
    void parseOBJLine(const std::string& line);
};