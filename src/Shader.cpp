#include "Shader.hpp"
#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "utils.hpp"

// Constructeur : charge, compile et link les shaders
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath){
    std::string vertexCode = loadFile(vertexPath);
    std::string fragmentCode = loadFile(fragmentPath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Active ce shader
void Shader::use() const{
    glUseProgram(ID);
}

void Shader::setUniform(const std::string& name, const glm::mat4& mat) const{
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniform(const std::string& name, const glm::vec3& vec) const{
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(location, 1, &vec[0]);
}

void Shader::setUniform(const std::string& name, float value) const{
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform1fv(location, 1, &value);
}

void Shader::setUniform(const std::string& name, int value) const{
    GLint location = glGetUniformLocation(ID, name.c_str());
    glUniform1iv(location, 1, &value);
}

std::string Shader::loadFile(const std::string& path)const{
    std::ifstream file(path);
    std::stringstream buffer;

    if (!file.is_open()){
        std::cerr << __func__ <<"Erreur lors de l'ouverture du fichier." << std::endl;
        return "";
    } 

    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& source) const{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    checkCompileErrors(shader, (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"));

    return shader;
}

void Shader::checkCompileErrors(GLuint shader, const std::string& type) const{
    GLint success;
    GLchar infoLog[1024];

    if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Erreur de LINKING (" << type << ") :\n" << infoLog << std::endl;
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Erreur de COMPILATION (" << type << ") :\n" << infoLog << std::endl;
        }
    }
}