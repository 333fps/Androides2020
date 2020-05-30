#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

struct GameData
{
	StateMachine stateMachine;
	sf::RenderWindow window;
	AssetManager assetManager;
	InputManager inputManager;
};

typedef std::shared_ptr<GameData> GameDataRef;

class GameEngine
{
public:
	GameEngine(int p_width, int p_height, std::string p_title);

private:
	const float dt = 1.0f / 60.0f;
	sf::Clock m_clock;

	GameDataRef m_data = std::make_shared<GameData>();

	void Run();
};

#endif // !_GAME_ENGINE_H_
