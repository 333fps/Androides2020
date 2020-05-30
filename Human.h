#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Human : public Sprite
{
public:
	Human(GameDataRef p_data, sf::Vector2f p_startPosition, std::vector<std::string>& p_path, std::unique_ptr<std::vector<std::string>>& p_level) :
		Sprite(p_data, p_startPosition, p_path, p_level)
	{
		//std::cout << "Human Created\t\t\t" << this << std::endl;
	}
	~Human()
	{
		//std::cout << "**Human Destroyed\t\t" << this << std::endl;
	}
private:
	void NextMotion();

public:
	void Update(float p_deltaTime);
	sf::Vector2f* GetHumanPosition();
	bool& isDigging();
};

#endif // !_HUMAN_H_
