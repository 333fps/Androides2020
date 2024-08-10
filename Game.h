#ifndef _GAME_H_
#define _GAME_H_

#include "GameEngine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
public:
	Game(GameDataRef p_data);

	~Game();

private:
	GameDataRef m_data;

	sf::Font m_font;
	sf::Text m_str_txtScore;
	sf::Text m_str_txtLives;
	sf::Text m_str_txtLevel;

	sf::Text m_str_valScore;
	sf::Text m_str_valLives;
	sf::Text m_str_valLevel;

	sf::Text m_str_valTimer;

	int m_levelTimer;
	int m_totalBonus;
	int* m_remainingBonus;
	int m_remaingLives{ 6 };

	int m_levelScore{ 0 };
	int m_totalScore{ 0 };

	bool m_isPlayerWin{ false };
	bool m_isPlayerLost{ false };

	float m_dtTotal;

	sf::Vector2f m_playerStartPosition;
	bool m_isBlinking{ false };
	bool m_isBlinkerOn{ false };

	sf::Clock m_clock;
	sf::Clock m_blinkClock;
	sf::RectangleShape m_blinkerRect;
	sf::Sprite m_blinker;

	bool m_isGameStarted{ false };

	std::vector<bool*> m_androidCatch{ 0 };
	bool* m_humanDig = nullptr;

	sf::Sound m_beep;
	sf::Sound m_catch;
	sf::Sound m_tick;
	sf::Sound m_tada;
	sf::Sound m_bonus;
	sf::Sound m_dig;

	bool m_isVictory{ false };
	bool m_isDefeat{ false };

	float dtMax = 1;

private:
	void Blink();
	void ChangeBlinkTexture();
	void LevelScore();
	void Timer(float dt);
	void RemainingLives();

public:
	void NewLevel();
	void SetPlayerStartPosition(sf::Vector2f p_playerStartPosition);
	void SetAndroidCatch(bool& p_catch);
	void SetHumanDig(bool& p_dig);

	void SetLevel(int p_levelNumber);
	void SetTimer(int p_levelTimer);
	void SetTotalBonus(int p_totalBonus);
	void SetRemainingBonus(int& p_remainingBonus);
	bool* IsVictory();
	bool* IsDefeat();
	int* GetRemainingLives();

	bool IsGameStarted() const;
	void StartBlinker();

	int GetFinalSCore() const;

	void Update(float dt);
	void Draw();
};

#endif // !_GAME_H_
