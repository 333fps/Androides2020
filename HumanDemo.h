#ifndef _HUMAN_DEMO_H_
#define _HUMAN_DEMO_H_

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class HumanDemo : public Sprite
{
public:
	HumanDemo(GameDataRef p_data, sf::Vector2f p_startPosition, std::vector<std::string>& p_path, std::unique_ptr<std::vector<std::string>>& p_level) :
		Sprite(p_data, p_startPosition, p_path, p_level)
	{
		//std::cout << "Human Created\t\t\t" << this << std::endl;
	}
	~HumanDemo()
	{
		//std::cout << "**Human Destroyed\t\t" << this << std::endl;
	}
private:
	void NextMotion();

	bool m_step1{ false };
	bool m_step2{ false };
	bool m_step3{ false };
	bool m_step4{ false };
	bool m_step5{ false };
	bool m_step6{ false };
	bool m_step7{ false };
	bool m_step8{ false };
	bool m_step9{ false };
	bool m_step10{ false };

	bool m_endDemo{ false };

public:
	bool EndDemo();
	void Update(float p_deltaTime);
	sf::Vector2f* GetHumanPosition();
};

#endif // !_HUMAN_DEMO_H_
