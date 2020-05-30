#ifndef _STATE_SPLASH_SCREEN_H_
#define _STATE_SPLASH_SCREEN_H_

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameEngine.h"
#include "SplashScreen.h"
#include "Transition.h"

#include <memory>
#include <iostream>

class StateSplash : public State
{
public:
	StateSplash(GameDataRef p_data);
	~StateSplash()
	{
		//std::cout << "**State Splashscreen Destroyed\t" << this << std::endl;
	}

private:
	GameDataRef m_data;

	std::unique_ptr<SplashScreen> m_splashScreen;
	std::unique_ptr<Transition> m_fadeOut;

	sf::Clock m_clock;

	bool m_isStateOver{ false };

	void ToggleFullscren();
	bool Fullscreen{ false };

private:
	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

#endif // !_STATE_SPLASH_SCREEN_H_
