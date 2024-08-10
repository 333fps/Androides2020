#ifndef _STATE_GAME_OVER_H_
#define _STATE_GAME_OVER_H_

#include "StateMenu.h"

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

class StateGameOver : public State
{
public:
	StateGameOver(GameDataRef p_data, int p_finalScore, int p_finalLevel);

	StateGameOver(StateGameOver&) = delete;
	StateGameOver& operator=(StateGameOver&) = delete;

	virtual ~StateGameOver();

private:
	GameDataRef m_data;

	std::unique_ptr<Transition> m_fadeIn;
	std::unique_ptr<Transition> m_fadeOut;

	std::unique_ptr<CurrentLevel> m_currentLevel;
	std::unique_ptr<Map> m_map;
	std::vector<std::shared_ptr<AndroidDemo>> m_androids;

	int m_finalScore{ 0 };
	int m_finalLevel{ 0 };

	sf::Text m_str_finalScore;
	sf::Text m_str_finalLevel;

	sf::Text m_str_valFinalScore;
	sf::Text m_str_valFinalLevel;

	void Score();
	void Level();

	bool m_isStateOver{ false };

	sf::Text m_str_credits1;
	sf::Text m_str_credits2;

	void ToggleFullscren();
	bool Fullscreen{ false };

	//bool m_GotoMenu{ false };

private:
	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

#endif // !_STATE_GAME_OVER_H_
