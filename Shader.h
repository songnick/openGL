//
// Created by qfsong on 2022/7/20.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned  int ID;
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            //close file
            vShaderFile.close();
            fShaderFile.close();
            //convert to code
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }catch (std::ifstream::failure& e){
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }

        const char* vertex = vertexCode.c_str();
        const char* fragment = fragmentCode.c_str();
        //compile shader
        unsigned int vertexShader, fragmentShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex ,NULL);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "vertex_type");

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment, NULL);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "fragment_type");
        //user program and attach shader, then link program
        ID = glCreateProgram();
        glAttachShader(ID,vertexShader);
        glAttachShader(ID,fragmentShader);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        //delete used shader
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};


#endif //OPENGL_SHADER_H
