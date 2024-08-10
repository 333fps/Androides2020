#ifndef _STATE_DEMO_H_
#define _STATE_DEMO_H_

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameEngine.h"
#include "Transition.h"
#include "CurrentLevel.h"
#include "Map.h"
#include "HumanDemo.h"
#include "Android.h"
#include "Game.h"

class StateDemo : public State
{
public:
	StateDemo(GameDataRef p_data);

	StateDemo(StateDemo&) = delete;
	StateDemo& operator=(StateDemo&) = delete;

	virtual ~StateDemo();

	GameDataRef m_data;

	std::unique_ptr<Transition> m_fadeIn;
	std::unique_ptr<Transition> m_fadeOut;

	std::unique_ptr<CurrentLevel> m_currentLevel;
	std::unique_ptr<Map> m_map;
	std::shared_ptr<HumanDemo> m_human;
	std::vector<std::shared_ptr<Android>> m_androids;

	bool m_isStateOver{ false };
	bool m_pause{ true };

	int m_levelNumber{ 1 };

	sf::Text m_str_backToMenu1;
	sf::Text m_str_backToMenu2;

	void ToggleFullscren();
	bool Fullscreen{ false };

private:
	void Init();
	void Start();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

#endif // !_STATE_DEMO_H_
