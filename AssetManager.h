#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

class AssetManager
{
public:
	AssetManager() { }
	~AssetManager() { }

	void LoadTexture(std::string p_textureName, std::string p_fileName);
	sf::Texture& GetTexture(std::string p_textureName);

	void SetRect(std::string p_rectName, int p_left, int p_top, int p_width, int p_height);
	sf::IntRect GetRect(std::string p_rectName);

	void LoadSound(std::string p_soundName, std::string p_fileName);
	sf::SoundBuffer& GetSound(std::string p_soundName);

	void LoadFont(std::string p_fontName, std::string p_fileName);
	sf::Font& GetFont(std::string p_fontName);

private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::IntRect> m_rects;
	std::map<std::string, sf::SoundBuffer> m_sounds;
};

#endif // !_ASSET_MANAGER_H_
