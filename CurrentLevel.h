#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Levels.h"
#include <memory>

class CurrentLevel
{
public:
	CurrentLevel(unsigned int p_levelNumber);

	CurrentLevel(CurrentLevel&) = delete;
	CurrentLevel& operator=(CurrentLevel&) = delete;

	~CurrentLevel();

private:
	std::unique_ptr<Levels> m_level;
	std::unique_ptr<std::vector<std::string>> m_currentLevel;

	std::string m_levelSettings;
	sf::Vector2f m_humanStartPosition;
	std::vector<sf::Vector2f> m_androidsStartPositions;

	sf::Color m_levelColor;
	int m_levelTimer;
	int m_totalBonus{ 0 };

private:
	void HumanStartPosition();
	void AndroidsStartPositions();
	void LevelColor();
	void LevelTimer();
	void CleanLevel();

public:
	std::unique_ptr<std::vector<std::string>>& GetLevel();
	sf::Color& GetLevelColor();
	int& GetLevelTimer();
	int& GetTotalBonus();

	const sf::Vector2f& GetHumanStartPosition() const;
	const std::vector<sf::Vector2f> GetAndroidsStartPositions() const;
};

#endif // !_LEVEL_H_
