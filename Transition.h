#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include "DEFINITIONS.h"
#include "GameEngine.h"

#include <array>
#include <iostream>
#include <string>

class Transition
{
public:
	Transition(GameDataRef p_data, std::string p_type, bool p_fullScreen);
	~Transition()
	{
		//std::cout << "**Transition Destroyed\t\t" << this << std::endl;
	}

private:
	bool m_type{ false };		// "FadeIn", "FadeOut"
	bool m_fullScreen{ false };

protected:
	bool m_isStarted{ false };
	bool m_isOver{ true };
	bool m_isCompleted{ false };

protected:
	GameDataRef m_data;
	int m_maxline{ 22 };
	unsigned int m_iStart{ 15 };
	unsigned int m_jStart{ 15 };
	sf::Sprite m_brickShape;
	sf::Sprite m_brickShapeScaled;

	sf::RectangleShape m_blackShape;
	float m_totalTime{ 0 };
	std::array<std::array<bool, 25>, 40> arr{ 0 };

public:
	bool IsInProgress();
	bool IsCompleted();
	void Start();
	void Update(float dt);
	void Draw();
};

#endif // !_TRANSITION_H_
