#include "Mesh.hpp"
#include <iostream>    // pour std::cout, std::cerr
#include <fstream>     // pour std::ifstream
#include <sstream>     // pour std::stringstream / istringstream
#include <string>      // pour std::string, std::getline

Mesh::Mesh(const std::string& filename){
    loadFromOBJ(filename);
}

bool Mesh::loadFromOBJ(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << __func__ <<"Erreur lors de l'ouverture du fichier." << std::endl;
        return false;
    } 

    std::string line;
    while (std::getline(file, line)) {
        parseOBJLine(line);
    }

    return true;
}

void Mesh::parseOBJLine(const std::string& line){
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix == "v") {
        float x, y, z;
        iss >> x >> y >> z;
        vertices.push_back(glm::vec3(x, y, z));
    } else if (prefix == "vn") {
        float x, y, z;
        iss >> x >> y >> z;
        normals.push_back(glm::vec3(x, y, z));
    } else if (prefix == "f") {
        std::string vertexStr;
        for (int i = 0; i < 3; ++i) {
            iss >> vertexStr;

            std::istringstream vss(vertexStr);
            std::string v_idx_str, vt_idx_str, vn_idx_str;

            std::getline(vss, v_idx_str, '/');
            std::getline(vss, vt_idx_str, '/');
            std::getline(vss, vn_idx_str, '/');

            int v_idx = std::stoi(v_idx_str);
            int vn_idx = std::stoi(vn_idx_str);

            indices.push_back(v_idx - 1);
            glm::vec3 normal = normals[vn_idx - 1];
            faceNormals.push_back(normal); 
        }
    }
}



