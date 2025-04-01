#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader (const std::string& vertPath, const std::string& fragPath) : programID ((0)) {
    this->loadShaders(vertPath, fragPath);
}

Shader::~Shader () {
    if (programID != 0) {
        glDeleteProgram (programID);
    }
}

static std::string readFile (const std::string& filePath) {
    std::ifstream file (filePath, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Could not open shader file: " << filePath << std::endl;
        return {};
    }
    std::stringstream buffer;
    buffer << file.rdbuf ();
    return buffer.str ();
}

bool Shader::loadShaders (const std::string& vertPath,
    const std::string& fragPath) {
    GLuint vertShader = 0;
    GLuint fragShader = 0;

    // Compile Vertex Shader
    if (!createShaderFromFile (vertPath, GL_VERTEX_SHADER, vertShader)) {
        return false;
    }

    // Compile Fragment Shader
    if (!createShaderFromFile (fragPath, GL_FRAGMENT_SHADER,
        fragShader)) {
        glDeleteShader (vertShader);
        return false;
    }

    // Link Program
    if (!linkProgram (vertShader, fragShader)) {
        glDeleteShader (vertShader);
        glDeleteShader (fragShader);
        return false;
    }


    // Shaders are now linked into the program, we can delete the shader objects
    glDeleteShader (vertShader);
    glDeleteShader (fragShader);

    return true;
}

bool Shader::createShaderFromFile (const std::string& filePath,
    GLuint shaderType,
    GLuint& shaderID) {
    // Read file
    std::string shaderSource = readFile (filePath);
    if (shaderSource.empty ()) {
        std::cerr << "Shader file is empty or failed to read: " << filePath <<
            std::endl;
        return false;
    }

    // Create shader
    shaderID                     = glCreateShader (shaderType);
    const char* shaderSourceCStr = shaderSource.c_str ();
    glShaderSource (shaderID, 1, &shaderSourceCStr, nullptr);
    glCompileShader (shaderID);

    // Check for compile errors
    if (!checkCompileErrors (shaderID, "SHADER")) {
        glDeleteShader (shaderID);
        return false;
    }

    return true;
}

bool Shader::linkProgram (unsigned int vertexShader,
    unsigned int fragmentShader) {
    // Create program if not already
    programID = glCreateProgram ();

    glAttachShader (programID, vertexShader);
    glAttachShader (programID, fragmentShader);
    glLinkProgram (programID);

    // Check for linking errors
    if (!checkLinkErrors (programID)) {
        glDeleteProgram (programID);
        programID = 0;
        return false;
    }
    return true;
}

bool Shader::checkCompileErrors (unsigned int shader,
    const std::string& type) {
    int success;
    glGetShaderiv (shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        int maxLength;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::string infoLog (maxLength, '\0');
        glGetShaderInfoLog (shader, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Shader Compile Error [" << type << "]:\n" << infoLog <<
            std::endl;
        return false;
    }
    return true;
}

bool Shader::checkLinkErrors (unsigned int program) {
    int success;
    glGetProgramiv (program, GL_LINK_STATUS, &success);
    if (!success) {
        int maxLength;
        glGetProgramiv (program, GL_INFO_LOG_LENGTH, &maxLength);

        std::string infoLog (maxLength, '\0');
        glGetProgramInfoLog (program, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Program Linking Error:\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

void Shader::use () const {
    if (programID != 0) {
        glUseProgram (programID);
    }
}


