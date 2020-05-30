#ifndef _ANDROID_DEMO_H_
#define _ANDROID_DEMO_H_

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class AndroidDemo : public Sprite
{
public:
	AndroidDemo(GameDataRef p_data, sf::Vector2f& p_startPosition, std::vector<std::string>& p_path, std::unique_ptr<std::vector<std::string>>& p_level) :
		Sprite(p_data, p_startPosition, p_path, p_level)
	{
		//std::cout << "Android Demo Created\t\t" << this << std::endl;
	}
	~AndroidDemo()
	{
		//std::cout << "**Android Demo Destroyed\t" << this << std::endl;
	}

private:
	void NextMotion();

public:
	void Update(float p_deltaTime);
};

#endif // !_ANDROID_DEMO_H_