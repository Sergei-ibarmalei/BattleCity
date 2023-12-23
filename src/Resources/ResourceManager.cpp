#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <iostream>
#include <sstream>
#include <fstream>


ResourceManager::ResourceManager(const std::string& executablePath)
{
	//»щем либо знак "/" либо знак "\"
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
	//std::cout << "===";
	//std::cout << m_path << std::endl;
}

std::shared_ptr<Renderer::ShaderProgram> 
	ResourceManager::loadShaders(const std::string& shaderName, 
	const std::string& vertexPath, 
	const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader, abort." << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentPath.empty())
	{
		std::cerr << "No fragment shader, abort." << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader =  m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexPath, fragmentPath)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}
	else
	{
		std::cerr << "Can't load shader program: \n"
			<< "Vertex: " << vertexPath << '\n'
			<< "Fragment: " << fragmentPath << '\n';
	}
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	shaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	else
	{
		std::cerr << "Can't find the shader program: " << shaderName << std::endl;
		return nullptr;
	}
}

std::string ResourceManager::getFileString(const std::string& relativePath) const
{
	std::ifstream f;
	f.open(m_path + '/' + relativePath.c_str(), std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cerr << "Failed to open file " << relativePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;

	buffer << f.rdbuf();
	std::cout << "------" << std::endl;
	std::cout << buffer.str() << std::endl;
	std::cout << "------" << std::endl;
	return buffer.str();
}
