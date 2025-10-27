#include "pch.h"
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"

namespace Project {

    Shader::Shader(const std::string& filepath) {
        ShaderSource source = ParseShader(filepath);
        m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

    }
    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }
    void Shader::Bind() const {
        glUseProgram(m_RendererID);

    }
    void Shader::Unbind() const {
        glUseProgram(0);

    }

    ShaderSource Shader::ParseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath);
        std::string line;
        std::stringstream ss[2];

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        ShaderType type = ShaderType::NONE;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else if (type != ShaderType::NONE)
            {
                ss[(int)type] << line << "\n";
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();

        glShaderSource(id, 1, &src, NULL);
        glCompileShader(id);

        int status;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            PROJECT_CORE_ERROR("Failed to compile {0} shader!", (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment");

            int length; 
            glGetShaderiv(id, GL_INFO_PROJECT_LENGTH, &length);
            
            if (length > 0) {
                char* log = (char*)alloca(sizeof(char) * length);
                glGetShaderInfoLog(id, length, NULL, log); 
                PROJECT_CORE_ERROR("{0} Shader Error Log : {1}\n", (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment", log);
            }
            else {
                PROJECT_CORE_ERROR("{0} Shader Error Log: (No info log available)\n", (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment");
            }

            glDeleteShader(id); 
            return 0;
        }
        return id; 
    }

    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int programID = glCreateProgram(); 
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        if (vs == 0 || fs == 0) { 
            PROJECT_CORE_ERROR("One or both shaders failed to compile. Not linking program.");
            glDeleteProgram(programID); 
            if (vs != 0) glDeleteShader(vs); 
            if (fs != 0) glDeleteShader(fs);
            return 0; 
        }

        glAttachShader(programID, vs);
        glAttachShader(programID, fs);
        glLinkProgram(programID);

        int linkStatus;
        glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
        if (linkStatus == GL_FALSE) {
            PROJECT_CORE_ERROR("Shader program linking FAILED!");
            int length;
            glGetProgramiv(programID, GL_INFO_PROJECT_LENGTH, &length);
            if (length > 0) {
                char* message = (char*)alloca(length * sizeof(char));
                glGetProgramInfoLog(programID, length, NULL, message);
                PROJECT_CORE_ERROR("Program Link Error Log: {0}", message);
            }
            else {
                PROJECT_CORE_ERROR("Program Link Error Log: (No info log available)\n");
            }
            glDeleteProgram(programID);
            glDeleteShader(vs);
            glDeleteShader(fs);
            return 0; 
        }

        glValidateProgram(programID); 
        int validateStatus;
        glGetProgramiv(programID, GL_VALIDATE_STATUS, &validateStatus);
        if (validateStatus == GL_FALSE) {
            PROJECT_CORE_ERROR("Shader program validation FAILED!");
            int length;
            glGetProgramiv(programID, GL_INFO_PROJECT_LENGTH, &length);
            if (length > 0) {
                char* message = (char*)alloca(length * sizeof(char));
                glGetProgramInfoLog(programID, length, NULL, message);
                PROJECT_CORE_ERROR("Program Validation Error Log: {0}", message);
            }
            else {
                PROJECT_CORE_ERROR("Program Validation Error Log: (No info log available)\n");
            }
            
        }

        glDetachShader(programID, vs); 
        glDetachShader(programID, fs);
        glDeleteShader(vs); 
        glDeleteShader(fs);

        return programID;
    }

    void Shader::SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void Shader::SetMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetVec3(const std::string& name, glm::vec3 value) const
    {
        glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
    }

}
