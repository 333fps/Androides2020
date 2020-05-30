#ifndef _MAP_H_
#define _MAP_H_

#include "GameEngine.h"
#include "DEFINITIONS.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

class Map
{
public:
	Map(GameDataRef p_data, std::unique_ptr<std::vector<std::string>>& p_level, sf::Color& p_levelColor);
	~Map()
	{
		//std::cout << "**Map Destroyed\t\t\t" << this << std::endl;
	}

private:
	GameDataRef m_data;

	std::unique_ptr<std::vector<std::string>>& m_level;
	sf::Color& m_levelColor;

	sf::Vector2u m_spritesheetTileSize{ 16, 16 };

	const unsigned int m_maxCol{ 40 };
	const unsigned int m_maxLine{ 22 };

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	std::vector<std::string> m_path;

	sf::Clock clock;

	std::vector<std::vector<int>> m_holesCoords;
	std::vector<sf::Clock> m_holesTimers;

	float m_scaledTileSizeX{ static_cast<float>(TILE_SIZE) };
	float m_scaledTileSizeY{ static_cast<float>(TILE_SIZE) };

	int m_remainingBonus;

private:
	void Load();
	void CreatePath();
	void GetNewHolesCoords();
	void HoleLife();

public:
	std::vector<std::string>& GetPath();
	int& GetRemainingBonus();

	void Update();
	void Draw();
	void DrawPath();
};

#endif // !_MAP_H_
