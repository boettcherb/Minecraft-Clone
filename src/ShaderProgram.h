#ifndef SHADER_PROGRAM_H_INCLUDED
#define SHADER_PROGRAM_H_INCLUDED

#include <string>
#include <vector>

class ShaderProgram {

	struct Shader {
		unsigned int m_id;
		std::string m_source;
		Shader(unsigned int id, const std::string& source);
	};

	unsigned int m_shaderProgramID;
	std::vector<Shader> m_shaders;

public:
	ShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~ShaderProgram();

	void bind() const;
	void unbind() const;

private:
	void compileAndLink() const;
	std::string parseShader(const std::string& filePath) const;
};

#endif