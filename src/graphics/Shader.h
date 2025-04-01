#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>


class Shader {
public:
    Shader(const std::string& vertPath, const std::string& fragPath);

    ~Shader();

    // Load vertex & fragment shaders from file paths
    bool loadShaders(const std::string &vertPath, const std::string &fragPath);

    void use() const;

    template<typename T>
    void setUniform(const std::string& name, const T& value)
    {
        if constexpr (std::is_same_v<T, glm::mat4>)
        {
            glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &value[0][0]);
        }
        else if constexpr (std::is_same_v<T, glm::vec3>)
        {
            glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, (GLfloat*)&value[0]);
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
        }
        else if constexpr (std::is_same_v<T, int>)
        {
            glUniform1i(glGetUniformLocation(programID, name.c_str()), (GLint)&value);
        }

    }

    unsigned int getID() const { return programID; }

private:
    GLuint programID = 0;

    bool createShaderFromFile(const std::string &filePath,
                              GLuint shaderType,
                              GLuint &shaderID);

    bool linkProgram(GLuint vertexShader, GLuint fragmentShader);

    bool checkCompileErrors(GLuint shader, const std::string &type);

    bool checkLinkErrors(GLuint program);
};


