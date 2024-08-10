#ifndef _ANDROID_H_
#define _ANDROID_H_

#include "Sprite.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Android : public Sprite
{
public:
	Android(GameDataRef p_data, const sf::Vector2f& p_startPosition, std::vector<std::string>& p_path,
		std::unique_ptr<std::vector<std::string>>& p_level, const sf::Vector2f* p_humanPostion, float p_dtOffset);

	Android(Android&) = delete;
	Android& operator=(Android&) = delete;

	virtual ~Android();

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
