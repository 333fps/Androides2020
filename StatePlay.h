#ifndef _STATE_PLAY_H_
#define _STATE_PLAY_H_

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameEngine.h"
#include "Transition.h"
#include "CurrentLevel.h"
#include "Map.h"
#include "Human.h"
#include "Android.h"
#include "Game.h"

class StatePlay : public State
{
public:
	StatePlay(GameDataRef p_data);
	~StatePlay()
	{
		//std::cout << "**State Play Destroyed\t\t" << this << std::endl;
	}

	GameDataRef m_data;

	std::unique_ptr<Transition> m_fadeIn;
	std::unique_ptr<Transition> m_fadeOut;

	std::unique_ptr<CurrentLevel> m_currentLevel;
	std::unique_ptr<Map> m_map;
	std::shared_ptr<Human> m_human;
	std::vector<std::shared_ptr<Android>> m_androids;

	bool m_isStateOver{ false };
	bool m_pause{ true };

	int m_levelNumber{ 1 };

	std::unique_ptr<Game> m_game;

	bool* m_isVictory;
	bool* m_isDefeat;
	bool* m_isGameStarted;
	int* m_remaingLives;

	bool m_totalWinner{ false };

	void ToggleFullscren();
	bool Fullscreen{ false };

	bool m_GotoMenu{ false };

private:
	void Init();
	void Start();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

#endif // !_STATE_PLAY_H_
