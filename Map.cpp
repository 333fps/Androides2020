#include "Map.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

Map::Map(GameDataRef p_data, std::unique_ptr<std::vector<std::string>>& p_level, sf::Color& p_levelColor) :
	m_data(p_data),
	m_level(p_level),
	m_levelColor(p_levelColor)
{
	//std::cout << "Map Created\t\t\t" << this << std::endl;

	m_tileset = m_data->assetManager.GetTexture("spritesheet");

	Load();
	CreatePath();
	//for (auto line : m_path)
	//	std::cout << line << std::endl;
}

void Map::Load()
{
	m_vertices.clear();
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_maxCol * m_maxLine * 4);

	int i = 0;

	for (auto line = m_level->begin(); line != m_level->end(); line++)
	{
		int j = 0;

		for (auto c = line->begin(); c != line->end(); ++c)
		{
			int tileID = 0;
			if (*c == '@')
				tileID = 12;
			if (*c == 'H')
				tileID = 15;
			if (*c == '_')
				tileID = 14;
			if (*c == '*')
			{
				tileID = 13;
			}
			if (tileID != 0)
			{
				int tu = tileID % (m_tileset.getSize().x / m_spritesheetTileSize.x);
				int tv = tileID / (m_tileset.getSize().x / m_spritesheetTileSize.x);

				sf::Vertex* quad = &m_vertices[(i + j * m_maxLine) * 4];

				quad[0].position = sf::Vector2f(j * m_scaledTileSizeX, i * m_scaledTileSizeY);
				quad[1].position = sf::Vector2f((j + 1) * m_scaledTileSizeX, i * m_scaledTileSizeY);
				quad[2].position = sf::Vector2f((j + 1) * m_scaledTileSizeX, (i + 1) * m_scaledTileSizeY);
				quad[3].position = sf::Vector2f(j * m_scaledTileSizeX, (i + 1) * m_scaledTileSizeY);

				quad[0].texCoords = sf::Vector2f((float)tu * m_spritesheetTileSize.x, (float)tv * m_spritesheetTileSize.y);
				quad[1].texCoords = sf::Vector2f(((float)tu + 1) * m_spritesheetTileSize.x, (float)tv * m_spritesheetTileSize.y);
				quad[2].texCoords = sf::Vector2f(((float)tu + 1) * m_spritesheetTileSize.x, ((float)tv + 1) * m_spritesheetTileSize.y);
				quad[3].texCoords = sf::Vector2f((float)tu * m_spritesheetTileSize.x, ((float)tv + 1) * m_spritesheetTileSize.y);

				if (tileID == 12)
				{
					quad[0].color = sf::Color(m_levelColor);
					quad[1].color = sf::Color(m_levelColor);
					quad[2].color = sf::Color(m_levelColor);
					quad[3].color = sf::Color(m_levelColor);
				}
			}
			++j;
		}
		i++;
	}
}

void Map::CreatePath()
{
	m_path.clear();
	for (auto line : *m_level)
	{
		m_path.push_back(line);
		m_path.push_back(line);
	}

	m_remainingBonus = 0;
	for (int i = 0; i < 44; ++i)
	{
		for (int j = 0; j < 40; ++j)
		{
			if (i > 0)
			{
				if (m_path[i][j] == '*')
				{
					m_path[i][j] = ' ';
					m_remainingBonus++;
				}
				if (m_path[i][j] == 'H')
				{
					if (m_path[i - 1][j] == ' ')
					{
						m_path[i - 1][j] = 'w';
					}

					m_path[i][j] = 'w';

					if (m_path[i - 1][j] == '@') //<-- Top of ladder
					{
						m_path[i][j] = '.';
					}
				}
				if (m_path[i][j] == '_')
				{
					m_path[i][j] = 'w';
					m_path[i - 1][j] = ' ';
				}
				if (m_path[i][j] == '@' && m_path[i - 1][j] != '@')
				{
					m_path[i - 1][j] = 'w';
				}

				if (m_path[i][j] != '@' && i == 43)
				{
					m_path[i][j] = 'w';
				}
				if (m_path[i][j] == 'T' && m_path[i + 1][j] == 'T')
				{
					m_path[i - 1][j] = 'w';
					m_path[i][j] = '@';
				}
			}
		}
	}

	//Falling area
	for (int i = 0; i < 44; ++i)
	{
		for (int j = 0; j < 40; ++j)
		{
			if (i > 1)
			{
				if (m_path[i][j] == ' ' && m_path[i - 1][j] == 'w')
				{
					m_path[i][j] = 'f';
				}
				if (m_path[i][j] == 'x' && m_path[i - 1][j] != '@')
				{
					m_path[i][j] = 'f';
					m_path[i - 1][j] = 'f';
				}
			}
			if (j > 1 && j < 40)
			{
				if (m_path[i][j] == ' ' && (m_path[i][j - 1] == 'w' || m_path[i][j + 1] == 'w'))
				{
					m_path[i][j] = 'f';
				}
			}
			if (j == 0)
			{
				if (m_path[i][j] == 'w' && m_path[i][j + 1] == ' ')
				{
					m_path[i][j + 1] = 'f';
				}
			}
		}
	}

	m_remainingBonus /= 2;
}

void Map::GetNewHolesCoords()
{
	int i = 0;
	for (auto& line : *m_level)
	{
		int j = 0;
		for (auto& c : line)
		{
			if (c == 'X')
			{
				c = 'x'; // <- to avoid to create clocks at every loop

				sf::Clock holesTimer;
				m_holesTimers.push_back(holesTimer);

				std::vector<int> holeCoords{ i, j };
				m_holesCoords.push_back(holeCoords);
			}
			j++;
		}
		i++;
	}
}

void Map::HoleLife()
{
	if (!m_holesTimers.empty())
	{
		auto timer = m_holesTimers.at(0);

		if (timer.getElapsedTime().asSeconds() > 4.5)
		{
			m_holesTimers.erase(m_holesTimers.begin());

			auto holesCoords = m_holesCoords.at(0);
			auto holeX = holesCoords.at(0);
			auto holeY = holesCoords.at(1);
			m_holesCoords.erase(m_holesCoords.begin());

			int i = 0;
			for (auto line = m_level->begin(); line != m_level->end(); line++)
			{
				int j = 0;
				for (auto it = line->begin(); it != line->end(); ++it)
				{
					if ((*it == 'x' || *it == 'T') && i == holeX && j == holeY)
					{
						*it = '@';
					}j++;
				}
				i++;
			}
		}
	}
}

std::vector<std::string>& Map::GetPath()
{
	return m_path;
}

int& Map::GetRemainingBonus()
{
	return m_remainingBonus;
}

void Map::Update()
{
	GetNewHolesCoords();
	HoleLife();
	Load();
	CreatePath();
}

void Map::Draw()
{
	this->m_data->window.draw(m_vertices, &m_tileset);
}

void Map::DrawPath()
{
	//for (unsigned int i = 0; i < m_maxLine * 2; ++i)
	//{
	//	for (unsigned int j = 0; j < m_maxCol; ++j)
	//	{
	//		if (m_path[i][j] == 'w')
	//		{
	//			sf::RectangleShape rectangle;
	//			rectangle.setSize(sf::Vector2f(m_scaledTileSizeX, m_scaledTileSizeY / 2));
	//			rectangle.setFillColor(sf::Color(0, 255, 0, 80));
	//			rectangle.setPosition(sf::Vector2f(j * m_scaledTileSizeX, i * m_scaledTileSizeY / 2));
	//			m_data->window.draw(rectangle);
	//		}
	//	}
	//}

	//for (unsigned int i = 0; i < m_maxLine * 2; ++i)
	//{
	//	for (unsigned int j = 0; j < m_maxCol; ++j)
	//	{
	//		if (m_path[i][j] == 'f')
	//		{
	//			sf::RectangleShape rectangle;
	//			rectangle.setSize(sf::Vector2f(m_scaledTileSizeX, m_scaledTileSizeY / 2));
	//			rectangle.setFillColor(sf::Color(255, 0, 0, 80));
	//			rectangle.setPosition(sf::Vector2f(j * m_scaledTileSizeX, i * m_scaledTileSizeY / 2));
	//			m_data->window.draw(rectangle);
	//		}
	//	}
	//}
}