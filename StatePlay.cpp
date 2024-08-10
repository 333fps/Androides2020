#include "StatePlay.h"
#include "StateGameOver.h"

#include "DEFINITIONS.h"

#include <memory>

StatePlay::StatePlay(GameDataRef p_data) : State{ p_data }, m_data(p_data)
{
}

StatePlay::~StatePlay()
{
}

void StatePlay::ToggleFullscren()
{
	this->Fullscreen = !this->Fullscreen;
	this->m_data->window.close();
	this->m_data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Androides 2020", this->Fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	this->m_data->window.setFramerateLimit(60);
}

void StatePlay::Init()
{
	this->m_game = std::make_unique<Game>(m_data);

	m_isVictory = m_game->IsVictory();
	m_isDefeat = m_game->IsDefeat();
	m_remaingLives = m_game->GetRemainingLives();

	this->Start();
}

void StatePlay::Start()
{
	this->m_pause = true;

	if (m_currentLevel == 0)
	{
		this->m_fadeIn = std::make_unique<Transition>(m_data, "FadeIn", true);
	}
	else
	{
		this->m_fadeIn = std::make_unique<Transition>(m_data, "FadeIn", false);
	}
	this->m_fadeOut = std::make_unique<Transition>(m_data, "FadeOut", false);

	m_androids.clear();
	m_human.reset();

	m_currentLevel = std::make_unique<CurrentLevel>(m_levelNumber);
	// m_currentLevel = std::make_unique<CurrentLevel>(3);

	m_map = std::make_unique<Map>(m_data, m_currentLevel->GetLevel(), m_currentLevel->GetLevelColor());

	m_human = std::make_shared<Human>(m_data, m_currentLevel->GetHumanStartPosition(), m_map->GetPath(), m_currentLevel->GetLevel());

	float dtoffset = 0;
	for (const auto& startPosition : m_currentLevel->GetAndroidsStartPositions())
	{
		auto android = std::make_shared<Android>(m_data, startPosition, m_map->GetPath(), m_currentLevel->GetLevel(), m_human->GetHumanPosition(), dtoffset);
		m_androids.push_back(android);
	}

	m_game->SetLevel(m_levelNumber);
	m_game->SetTimer(m_currentLevel->GetLevelTimer());
	m_game->SetTotalBonus(m_currentLevel->GetTotalBonus());
	m_game->SetRemainingBonus(m_map->GetRemainingBonus());

	m_game->NewLevel();

	m_game->SetPlayerStartPosition(m_currentLevel->GetHumanStartPosition());
	for (const auto& android : m_androids)
	{
		m_game->SetAndroidCatch(android->isCatching());
	}

	m_game->SetHumanDig(m_human->isDigging());

	this->m_fadeIn->Start();
}

void StatePlay::HandleInput()
{
	sf::Event event;

	while (this->m_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->m_data->window.close();
		}

		if (event.type == sf::Event::Resized)
		{
			auto m_window_width = event.size.width;
			auto m_window_height = event.size.height;
			float new_width = ASPECT_RATIO * (float)m_window_height;
			float new_height = (float)m_window_width / ASPECT_RATIO;
			float offset_width = ((float)m_window_width - new_width) / 2.0f;
			float offset_height = ((float)m_window_height - new_height) / 2.0f;
			sf::View view = m_data->window.getDefaultView();
			if ((float)m_window_width >= ASPECT_RATIO * (float)m_window_height)
			{
				view.setViewport(sf::FloatRect(offset_width / (float)m_window_width, 0.f, new_width / (float)m_window_width, 1.f));
			}
			else
			{
				view.setViewport(sf::FloatRect(0.f, offset_height / (float)m_window_height, 1.f, new_height / (float)m_window_height));
			}

			m_data->window.setView(view);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			m_GotoMenu = true;
			m_fadeOut->Start();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			ToggleFullscren();
		}
	}
}

void StatePlay::Update(float dt)
{
	if (*m_isVictory && !m_pause)
	{
		m_pause = true;

		m_levelNumber++;
		if (m_levelNumber == 11)
		{
			m_totalWinner = true;
		}
		m_fadeOut->Start();
	}

	if (*m_isDefeat && !m_pause)
	{
		m_pause = true;
		m_fadeOut->Start();
	}

	if (this->m_fadeIn->IsInProgress() && this->m_pause)
	{
		this->m_fadeIn->Update(dt);
	}

	if (this->m_fadeIn->IsCompleted() && this->m_pause && !*m_isVictory)
	{
		this->m_pause = false;
		this->m_game->StartBlinker();
	}

	if (!m_pause && m_game->IsGameStarted() && !*m_game->IsDefeat())
	{
		m_map->Update();

		m_human->Update(dt);

		for (auto const& android : m_androids)
		{
			android->Update(dt);
		}
	}

	m_game->Update(dt);

	if (this->m_fadeOut->IsInProgress())
	{
		this->m_fadeOut->Update(dt);
	}

	if (this->m_fadeOut->IsCompleted())
	{
		if (m_totalWinner && !m_GotoMenu)
		{
			this->m_data->stateMachine.AddState(StateRef(new StateGameOver(m_data, m_game->GetFinalSCore(), m_levelNumber)), true);
		}

		if (*m_remaingLives == 0 && !m_GotoMenu)
		{
			this->m_data->stateMachine.AddState(StateRef(new StateGameOver(m_data, m_game->GetFinalSCore(), m_levelNumber)), true);
		}
		else
		{
			this->Start();
		}
		if (m_GotoMenu)
		{
			this->m_data->stateMachine.AddState(StateRef(new StateMenu(m_data)), true);
		}
	}
}

void StatePlay::Draw(float dt)
{
	(void)dt;
	this->m_data->window.clear();

	this->m_human->Draw();

	for (auto const& android : m_androids)
	{
		android->Draw();
	}

	this->m_map->Draw();
	// this->m_map->DrawPath();

	this->m_game->Draw();

	this->m_fadeIn->Draw();
	this->m_fadeOut->Draw();

	this->m_data->window.display();
}
