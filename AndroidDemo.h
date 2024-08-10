#ifndef _ANDROID_DEMO_H_
#define _ANDROID_DEMO_H_

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class AndroidDemo : public Sprite
{
public:
	AndroidDemo(GameDataRef p_data, sf::Vector2f& p_startPosition, std::vector<std::string>& p_path,
		std::unique_ptr<std::vector<std::string>>& p_level);

	AndroidDemo(AndroidDemo&) = delete;
	AndroidDemo& operator=(AndroidDemo&) = delete;

	virtual ~AndroidDemo();

private:
	void NextMotion();

public:
	void Update(float p_deltaTime);
};

#endif // !_ANDROID_DEMO_H_
