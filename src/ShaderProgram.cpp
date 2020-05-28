#include "ShaderProgram.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

ShaderProgram::Shader::Shader(unsigned int id, const std::string& source)
    : m_id{ id }, m_source{ source } {}

ShaderProgram::ShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
	m_shaderProgramID = glCreateProgram();
    m_shaders.emplace_back(glCreateShader(GL_VERTEX_SHADER), parseShader(vertexFilePath));
    m_shaders.emplace_back(glCreateShader(GL_FRAGMENT_SHADER), parseShader(fragmentFilePath));
    compileAndLink();

    // the individual shaders are not needed after they have been linked into one program
    for (const ShaderProgram::Shader& shader : m_shaders) {
        glDeleteShader(shader.m_id);
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_shaderProgramID);
}

void ShaderProgram::compileAndLink() const {
    int success = 0;
    for (const ShaderProgram::Shader& shader : m_shaders) {
        const char* src = shader.m_source.c_str();
        glShaderSource(shader.m_id, 1, &src, nullptr);
        glCompileShader(shader.m_id);

        // make sure the shader compiled successfully
        glGetShaderiv(shader.m_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512] = { 0 };
            glGetShaderInfoLog(shader.m_id, 512, nullptr, infoLog);
            std::cerr << "Shader Compilation Failed\n" << infoLog << '\n';
        }

        // combine each individual shader into one program
        glAttachShader(m_shaderProgramID, shader.m_id);
    }

    glLinkProgram(m_shaderProgramID);

    // make sure the shader program linked successfully
    glValidateProgram(m_shaderProgramID);
    glGetProgramiv(m_shaderProgramID, GL_VALIDATE_STATUS, &success);
    if (!success) {
        std::cerr << "Shader Program Linking Failed\n";
    }
}

std::string ShaderProgram::parseShader(const std::string& filePath) const {
    std::ifstream stream(filePath);
    if (!stream) {
        std::cerr << "Could not find/open shader at " << filePath << '\n';
    }
    std::string shaderSource;
    while (stream) {
        std::string line;
        std::getline(stream, line);
        shaderSource += line + '\n';
    }
    return shaderSource;
}

void ShaderProgram::bind() const {
    glUseProgram(m_shaderProgramID);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}