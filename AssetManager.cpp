#include "AssetManager.h"

void AssetManager::LoadTexture(std::string p_textureName, std::string p_fileName)
{
	sf::Texture texture;

	if (texture.loadFromFile(p_fileName))
	{
		this->m_textures[p_textureName] = texture;
	}
}

sf::Texture& AssetManager::GetTexture(std::string name)
{
	return this->m_textures.at(name);
}

void AssetManager::SetRect(std::string p_rectName, int p_left, int p_top, int p_width, int p_height)
{
	sf::IntRect rect;
	rect.left = p_left;
	rect.top = p_top;
	rect.width = p_width;
	rect.height = p_height;

	this->m_rects[p_rectName] = rect;
}

sf::IntRect AssetManager::GetRect(std::string p_rectName)
{
	return this->m_rects.at(p_rectName);
}

void AssetManager::LoadSound(std::string p_soundName, std::string p_fileName)
{
	sf::SoundBuffer buffer;

	if (buffer.loadFromFile(p_fileName))
	{
		this->m_sounds[p_soundName] = buffer;
	}
}

sf::SoundBuffer& AssetManager::GetSound(std::string p_soundName)
{
	return this->m_sounds.at(p_soundName);
}

void AssetManager::LoadFont(std::string p_fontName, std::string p_fileName)
{
	sf::Font font;

	if (font.loadFromFile(p_fileName))
	{
		this->m_fonts[p_fontName] = font;
	}
}

sf::Font& AssetManager::GetFont(std::string name)
{
	return this->m_fonts.at(name);
}