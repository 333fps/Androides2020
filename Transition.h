#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include "DEFINITIONS.h"
#include "GameEngine.h"

#include <array>
#include <string>

class Transition
{
public:
	Transition(GameDataRef p_data, std::string p_type, bool p_fullScreen);

	~Transition();

protected:
	bool m_isStarted{ false };
	bool m_isOver{ true };
	bool m_isCompleted{ false };

protected:
	GameDataRef m_data;
	size_t m_maxline{ 22 };
	size_t m_iStart{ 15 };
	size_t m_jStart{ 15 };
	sf::Sprite m_brickShape;
	sf::Sprite m_brickShapeScaled;

	sf::RectangleShape m_blackShape;
	float m_totalTime{ 0 };
	std::array<std::array<bool, 25>, 40> arr{};

private:
	bool m_type{ false }; // "FadeIn", "FadeOut"
	bool m_fullScreen{ false };

public:
	bool IsInProgress() const;
	bool IsCompleted() const;
	void Start();
	void Update(float dt);
	void Draw();
};

#endif // !_TRANSITION_H_
