#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

#ifdef _WIN32 
	#define SYMBOL "\\"
#else 
	#define SYMBOL "//"
#endif

ResourceManager::ResourceManager(const std::string& executablePath)
{

	size_t found = executablePath.find_last_of(SYMBOL);
	m_path = executablePath.substr(0, found);

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



	std::shared_ptr<Renderer::ShaderProgram>& newShader =  
		m_shaderPrograms.emplace(shaderName, 
		std::make_shared<Renderer::ShaderProgram>(vertexString, 
			                                    fragmentString)).first->second;
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

void ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	//количество каналов получаемых из текстуры
	int channels = 0;
	//размеры текстуры
	int width = 0;
	int height = 0;



	//данные загружать снизу-вверх, а не сверху вниз(особенность openGL)
	stbi_set_flip_vertically_on_load(true); 
	//загружаем текстуру используя библиотеку stb
	unsigned char* pixels = 
		stbi_load(std::string(m_path + SYMBOL + texturePath).c_str(),
		&width, &height, &channels, 0);
	if (!pixels)
	{
		std::cerr << "Can't load picture " << texturePath << std::endl;
		return;
	};


	stbi_image_free(pixels);
}



std::string ResourceManager::getFileString(const std::string& relativePath) const
{
	std::ifstream f;
	//f.open(m_path + '\\' + relativePath.c_str(), std::ios::in | std::ios::binary);
	f.open(m_path + SYMBOL + relativePath.c_str(), std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cerr << "Failed to open file " << relativePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;


	buffer << f.rdbuf();
	return buffer.str();
}
