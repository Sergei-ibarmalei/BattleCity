#pragma once
#include <glad/glad.h>
#include <string>


namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader,
			const std::string& fragmentShader);
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void  Use() const;

	private:
		bool createShader(const std::string& source,
			const GLenum shaderType,
			GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}