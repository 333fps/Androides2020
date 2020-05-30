#include "CurrentLevel.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

CurrentLevel::CurrentLevel(unsigned int p_levelNumber)
{
	this->m_level = std::make_unique<Levels>(p_levelNumber);
	m_currentLevel = m_level->GetLevel();
	m_levelSettings = m_currentLevel->at(22);
	m_currentLevel->pop_back();

	HumanStartPosition();
	AndroidsStartPositions();
	LevelColor();
	LevelTimer();
	CleanLevel();
}

void CurrentLevel::HumanStartPosition()
{
	int i = 0;
	for (auto line : *m_currentLevel)
	{
		int j = 0;
		for (auto c : line)
		{
			if (c == '&')
			{
				m_humanStartPosition.x = j * 16.0f;
				m_humanStartPosition.y = i * 16.0f + 8.0f;
			}
			j++;
		}
		i++;
	}
}

void CurrentLevel::AndroidsStartPositions()
{
	int i = 0;
	for (auto line : *m_currentLevel)
	{
		int j = 0;
		for (auto c : line)
		{
			if (c == 'A')
			{
				sf::Vector2f androidPosition;
				androidPosition.x = j * 16.0f;
				androidPosition.y = i * 16.0f + 8.0f;
				m_androidsStartPositions.push_back(androidPosition);
			}
			j++;
		}
		i++;
	}
}

void CurrentLevel::LevelColor()
{
	std::string strRGBr = m_levelSettings.substr(0, 3);
	int m_RGBr = std::stoi(strRGBr);

	std::string strRGBg = m_levelSettings.substr(3, 3);
	int m_RGBg = std::stoi(strRGBg);

	std::string strRGBb = m_levelSettings.substr(6, 3);
	int m_RGBb = std::stoi(strRGBb);

	std::string strRGBa = m_levelSettings.substr(9, 3);
	int m_RGBa = std::stoi(strRGBa);

	m_levelColor = sf::Color(m_RGBr, m_RGBg, m_RGBb, m_RGBa);
}

void CurrentLevel::LevelTimer()
{
	std::string levelTimer = m_levelSettings.substr(12, 3);
	m_levelTimer = std::stoi(levelTimer);
}

void CurrentLevel::CleanLevel()
{
	int i = 0;
	for (auto line = m_currentLevel->begin(); line != m_currentLevel->end(); line++)
	{
		int j = 0;
		for (auto c = line->begin(); c != line->end(); ++c)
		{
			if (*c == '&' || *c == 'A')
			{
				*c = ' ';
			}
			if (*c == '*')
			{
				++m_totalBonus;
			}

			j++;
		}
		i++;
	}
}

std::unique_ptr<std::vector<std::string>>& CurrentLevel::GetLevel()
{
	return m_currentLevel;
}

sf::Color& CurrentLevel::GetLevelColor()
{
	return m_levelColor;
}

int& CurrentLevel::GetLevelTimer()
{
	return m_levelTimer;
}

int& CurrentLevel::GetTotalBonus()
{
	return m_totalBonus;
}

const sf::Vector2f& CurrentLevel::GetHumanStartPosition() const
{
	return  m_humanStartPosition;
}

const std::vector<sf::Vector2f> CurrentLevel::GetAndroidsStartPositions() const
{
	return m_androidsStartPositions;
}