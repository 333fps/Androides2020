#ifndef _ANDROID_H_
#define _ANDROID_H_

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Android : public Sprite
{
public:
	Android(GameDataRef p_data, sf::Vector2f& p_startPosition, std::vector<std::string>& p_path, std::unique_ptr<std::vector<std::string>>& p_level, const sf::Vector2f* p_humanPostion, float p_dtOffset) : //Androids
		Sprite(p_data, p_startPosition, p_path, p_level, p_humanPostion, p_dtOffset),
		m_target(*p_humanPostion)
	{
		//std::cout << "Android Created\t\t\t" << this << std::endl;

		m_dtMax = 0.12f + p_dtOffset;
	}
	~Android()
	{
		//std::cout << "**Android Destroyed\t\t" << this << std::endl;
	}

private:
	const sf::Vector2f& m_target;
	bool m_catch{ false };

	void NextMotion();

public:
	void UpdateCatch();
	bool& isCatching();
	void Update(float p_deltaTime);
};
#endif
