#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "GameEngine.h"
#include "DEFINITIONS.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Sprite
{
public:

	Sprite(GameDataRef p_data, sf::Vector2f& p_startPosition, std::vector<std::string>& p_path, std::unique_ptr<std::vector<std::string>>& p_level, const sf::Vector2f* p_humanPostion, float p_dtOffset); //Androids

	Sprite(GameDataRef p_data, sf::Vector2f& p_startPosition, std::vector<std::string>& p_path, std::unique_ptr<std::vector<std::string>>& p_level); //Human

	~Sprite()
	{
	}

	GameDataRef m_data;

	std::vector<std::string>& m_level;
	std::vector<std::string>& m_path;
	sf::Vector2f& m_startPosition;

	float m_totalTime{ 0.0f };

	//RUN
	int m_runFrame{ 0 };
	std::vector<sf::IntRect> m_animRun;
	sf::IntRect NextRunFrame();

	//ROPE
	int m_ropeFrame{ 0 };
	std::vector<sf::IntRect> m_animRope;
	sf::IntRect NextRopeFrame();

	sf::Sprite m_spriteShape;

	sf::Sprite m_spriteShapeScaled;

	sf::Vector2f m_nextPosition;
	sf::Vector2f m_presentPosition;

	float m_dtMax{ 0 };;

	void UpdateStatus();
	void CheckDirection();
	void IsFalling();
	void IsInWall();
	void IsOnRope();
	void IsOnLadder();
	void IsRunning();
	void IsWaiting();

	void UpdateTexture();

	bool m_direction{ true };
	bool m_isFalling{ false };
	bool m_isInWall{ false };
	bool m_isRunning{ false };
	bool m_isWaiting{ true };
	bool m_isOnRope{ false };
	bool m_isOnLadder{ false };
	bool m_isDigging{ false };

	void Init();
	bool IsInBounds();

	bool IsOnPath();

public:
	void Draw();
};

#endif // !_SPRITE_H_
