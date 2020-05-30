#ifndef _STATE_MENU_H_
#define _STATE_MENU_H_

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameEngine.h"
#include "Transition.h"
#include "CurrentLevel.h"
#include "Map.h"
#include "AndroidDemo.h"
#include "StatePlay.h"

#include <memory>

#include <string>
#include <iostream>

class StateMenu : public State
{
public:
	StateMenu(GameDataRef p_data);
	~StateMenu()
	{
		//std::cout << "**State Menu Destroyed\t\t" << this << std::endl;
	}

private:
	GameDataRef m_data;

	std::unique_ptr<Transition> m_fadeIn;
	std::unique_ptr<Transition> m_fadeOut;

	std::unique_ptr<CurrentLevel> m_currentLevel;
	std::unique_ptr<Map> m_map;
	std::vector<std::shared_ptr<AndroidDemo>> m_androids;

	bool m_isStateOver{ false };
	bool m_GotoDemo{ false };

	sf::Text m_str_start;
	sf::Text m_str_how_to1;
	sf::Text m_str_how_to2;
	sf::Text m_str_toggle_fullscreen;

	sf::Text m_str_demo_countdown;

	sf::Text m_str_credits1;
	sf::Text m_str_credits2;

	void SetTimer(int p_levelTimer);
	void Timer(float dt);
	float m_dtTotal{ 0 };

	int m_demoTimer{ 15 };

	void ToggleFullscren();
	bool Fullscreen{ false };

private:
	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

#endif // !_STATE_MENU_H_
