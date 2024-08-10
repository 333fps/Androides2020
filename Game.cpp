#include "DEFINITIONS.h"
#include "Game.h"

Game::Game(GameDataRef p_data) : m_data(p_data)
{
	// TEXT
	m_str_txtScore.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	m_str_txtScore.setCharacterSize(TILE_SIZE);
	m_str_txtScore.setString(sf::String("SCORE"));
	m_str_txtScore.setFillColor(sf::Color(042, 042, 255, 255));
	m_str_txtScore.setPosition(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE * 23));

	m_str_txtLives.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	m_str_txtLives.setCharacterSize(TILE_SIZE);
	m_str_txtLives.setString(sf::String("LIVES"));
	m_str_txtLives.setFillColor(sf::Color(042, 042, 255, 255));
	m_str_txtLives.setPosition(sf::Vector2f(TILE_SIZE * 15 + TILE_SIZE / 2, TILE_SIZE * 23));

	m_str_txtLevel.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	m_str_txtLevel.setCharacterSize(TILE_SIZE);
	m_str_txtLevel.setString(sf::String("LEVEL"));
	m_str_txtLevel.setFillColor(sf::Color(042, 042, 255, 255));
	m_str_txtLevel.setPosition(sf::Vector2f(TILE_SIZE * 24 + TILE_SIZE / 2, TILE_SIZE * 23));

	// VARIABLES
	m_str_valScore.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	m_str_valScore.setCharacterSize(TILE_SIZE);
	m_str_valScore.setString(sf::String("000000"));
	m_str_valScore.setFillColor(sf::Color(255, 000, 000, 255));
	m_str_valScore.setPosition(sf::Vector2f(TILE_SIZE * 6.5 + TILE_SIZE / 2, TILE_SIZE * 23));

	m_str_valLives.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	m_str_valLives.setCharacterSize(TILE_SIZE);
	m_str_valLives.setString(sf::String("3"));
	m_str_valLives.setFillColor(sf::Color(255, 000, 000, 255));
	m_str_valLives.setPosition(sf::Vector2f(21.5 * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE * 23));

	m_str_valLevel.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	m_str_valLevel.setCharacterSize(TILE_SIZE);
	m_str_valLevel.setString(sf::String("001"));
	m_str_valLevel.setFillColor(sf::Color(255, 000, 000, 255));
	m_str_valLevel.setPosition(sf::Vector2f(30.5 * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE * 23));

	m_str_valTimer.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	m_str_valTimer.setCharacterSize(TILE_SIZE);
	m_str_valTimer.setString(sf::String("0000"));
	m_str_valTimer.setFillColor(sf::Color(255, 255, 000, 255));
	m_str_valTimer.setPosition(sf::Vector2f(35.125 * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE * 23));

	this->m_blinker.setTexture(this->m_data->assetManager.GetTexture("spritesheet"));
	this->m_blinker.setTextureRect(this->m_data->assetManager.GetRect("wait"));
	this->m_blinker.setOrigin(sf::Vector2f(0.0f, 8.0f));
	this->m_blinker.setColor(sf::Color::Black);
	this->m_blinker.setScale(m_blinker.getScale() * SCALE_FACTOR);

	this->m_blinkerRect.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	this->m_blinkerRect.setOrigin(sf::Vector2f(0.0f, TILE_SIZE / 2));
	this->m_blinkerRect.setFillColor(sf::Color::Yellow);

	// Sounds
	this->m_beep.setBuffer(this->m_data->assetManager.GetSound("beep"));
	this->m_catch.setBuffer(this->m_data->assetManager.GetSound("hit"));
	this->m_tick.setBuffer(this->m_data->assetManager.GetSound("tick"));
	this->m_tada.setBuffer(this->m_data->assetManager.GetSound("win"));
	this->m_bonus.setBuffer(this->m_data->assetManager.GetSound("bonus"));
	this->m_dig.setBuffer(this->m_data->assetManager.GetSound("dig"));
}

Game::~Game()
{
}

void Game::ChangeBlinkTexture()
{
	if (m_isBlinking == false)
	{
		m_blinker.setColor(sf::Color::Black);
		m_blinkerRect.setFillColor(sf::Color::Yellow);
		m_beep.play();
		m_isBlinking = true;
	}
	else
	{
		m_blinker.setColor(sf::Color::Yellow);
		m_blinkerRect.setFillColor(sf::Color::Black);
		m_beep.play();
		m_isBlinking = false;
	}
}

void Game::Blink()
{
	if (m_clock.getElapsedTime().asSeconds() < 5)
	{
		if (m_blinkClock.getElapsedTime().asSeconds() > 1)
		{
			ChangeBlinkTexture();
			m_blinkClock.restart();
		}
	}
	else
	{
		m_isGameStarted = true;
		m_isBlinkerOn = false;
	}
}

void Game::LevelScore()
{
	auto previousScore = m_levelScore;
	m_levelScore = m_totalScore + (m_totalBonus - *m_remainingBonus) * 40;

	if (previousScore != m_levelScore && !m_isPlayerWin && m_isGameStarted)
	{
		if (m_bonus.getStatus() == 0)
		{
			m_bonus.play();
		}
		if (m_bonus.getStatus() != 0)
		{
			m_bonus.stop();
			m_bonus.play();
		}
	}

	std::string tmp = std::to_string(m_levelScore);
	auto strLen = tmp.length();

	auto numberOfZero = 6 - strLen;

	std::string final = std::string(numberOfZero, '0').append(tmp);

	m_str_valScore.setString(sf::String(final));
}

void Game::Timer(float dt)
{
	if (m_levelTimer > 0)
	{
		m_dtTotal += dt;
		if (m_dtTotal >= 1)
		{
			m_levelTimer -= 1;
			this->SetTimer(m_levelTimer);
			m_dtTotal = 0.0f;
		}
	}
	else
	{
	}
}

void Game::RemainingLives()
{
	std::string tmp = std::to_string(m_remaingLives);
	m_str_valLives.setString(sf::String(tmp));
}

void Game::NewLevel()
{
	m_isPlayerWin = false;
	m_isVictory = false;
	m_isPlayerLost = false;
	m_isDefeat = false;
	m_isGameStarted = false;
	m_isBlinking = false;
	m_clock.restart();
	m_androidCatch.clear();
	RemainingLives();
}

void Game::SetPlayerStartPosition(sf::Vector2f p_playerStartPosition)
{
	m_blinker.setPosition(p_playerStartPosition * SCALE_FACTOR);
	m_blinkerRect.setPosition(p_playerStartPosition * SCALE_FACTOR);
}

void Game::SetAndroidCatch(bool& p_catch)
{
	m_androidCatch.push_back(&p_catch);
}

void Game::SetHumanDig(bool& p_dig)
{
	m_humanDig = &p_dig;
}

void Game::SetLevel(int p_levelNumber)
{
	std::string tmp = std::to_string(p_levelNumber);
	auto strLen = tmp.length();

	auto numberOfZero = 3 - strLen;

	std::string final = std::string(numberOfZero, '0').append(tmp);

	m_str_valLevel.setString(sf::String(final));
}

void Game::SetTimer(int p_levelTimer)
{
	m_levelTimer = p_levelTimer;
	std::string tmp = std::to_string(p_levelTimer);
	auto strLen = tmp.length();

	auto numberOfZero = 3 - strLen;

	std::string final = std::string(numberOfZero, '0').append(tmp);

	m_str_valTimer.setString(sf::String(final));
}

void Game::SetTotalBonus(int p_totalBonus)
{
	m_totalBonus = p_totalBonus;
}

void Game::SetRemainingBonus(int& p_remainingBonus)
{
	m_remainingBonus = &p_remainingBonus;
}

bool* Game::IsVictory()
{
	return &m_isVictory;
}

bool* Game::IsDefeat()
{
	return &m_isDefeat;
}

int* Game::GetRemainingLives()
{
	return &m_remaingLives;
}

bool Game::IsGameStarted() const
{
	return m_isGameStarted;
}

void Game::StartBlinker()
{
	m_isBlinkerOn = true;
}

int Game::GetFinalSCore() const
{
	return m_levelScore;
}

void Game::Update(float dt)
{
	if (!m_isGameStarted && m_isBlinkerOn && !m_isPlayerWin)
	{
		Blink();
	}
	if (m_isGameStarted && !m_isPlayerLost && !m_isPlayerWin)
	{
		Timer(dt);
	}

	if (!m_isPlayerLost)
	{
		for (auto b : m_androidCatch)
		{
			if (*b == true)
			{
				m_isPlayerLost = true;
				m_isGameStarted = false;

				if (m_catch.getStatus() == 0)
				{
					m_catch.play();
				}
			}
		}
	}

	if (*m_humanDig && m_dig.getStatus() == 0)
	{
		m_dig.play();
	}

	if (!m_isPlayerLost && m_isGameStarted && !m_isDefeat)
	{
		if (m_levelTimer <= 0)
		{
			m_isPlayerLost = true;
			m_isGameStarted = false;

			if (m_catch.getStatus() == 0)
			{
				m_catch.play();
			}
		}
	}

	if (m_catch.getStatus() == 0 && m_isPlayerLost && !m_isDefeat)
	{
		m_remaingLives--;
		m_isDefeat = true;
	}

	if (!m_isPlayerWin)
	{
		LevelScore();
	}

	if (*m_remainingBonus == 0 && !m_isPlayerWin && !m_isVictory)
	{
		m_isPlayerWin = true;
		m_isGameStarted = false;

		m_tada.play();
	}

	if (1 < m_levelTimer && m_levelTimer <= 10 && !m_isVictory)
	{
		if (m_blinkClock.getElapsedTime().asSeconds() > 1)
		{
			m_tick.play();

			m_blinkClock.restart();
		}
	}

	if (m_tada.getStatus() == 0 && m_isPlayerWin)
	{
		if (m_levelTimer > 0)
		{
			m_dtTotal += dt;
			if (m_dtTotal >= dtMax)
			{
				m_tick.stop();
				if (dtMax > 0.06f)
				{
					dtMax = dtMax * 0.6f;
				}
				m_levelTimer -= 1;
				m_tick.play();

				m_totalScore += 10;

				this->SetTimer(m_levelTimer);
				LevelScore();

				m_dtTotal = 0.0f;
			}
		}
		else
		{
			m_totalScore = m_levelScore;
			m_isVictory = true;
		}
	}
}

void Game::Draw()
{
	m_data->window.draw(m_str_txtScore);
	m_data->window.draw(m_str_txtLives);
	m_data->window.draw(m_str_txtLevel);

	m_data->window.draw(m_str_valScore);
	m_data->window.draw(m_str_valLives);
	m_data->window.draw(m_str_valLevel);
	m_data->window.draw(m_str_valTimer);

	if (!m_isGameStarted && !m_isPlayerWin && !m_isPlayerLost)
	{
		m_data->window.draw(m_blinkerRect);
		m_data->window.draw(m_blinker);
	}
}
