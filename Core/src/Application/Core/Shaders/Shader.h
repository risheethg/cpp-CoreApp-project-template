#pragma once
#include "glm/glm.hpp"

namespace Project {

    struct ShaderSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class Shader {
    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetID() const { return m_RendererID; }

        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetMat4(const std::string& name, glm::mat4 value) const;
        void SetVec3(const std::string& name, glm::vec3 value) const;

        inline unsigned int GetRendererID() const { return m_RendererID; }
    private:
        unsigned int m_RendererID;
        ShaderSource ParseShader(const std::string& filepath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    };

}
