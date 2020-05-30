#include "StateMenu.h"
#include "StatePlay.h"
#include "StateDemo.h"

#include "DEFINITIONS.h"

#include <iostream>
#include <memory>

StateMenu::StateMenu(GameDataRef p_data) : m_data(p_data)
{
	//std::cout << "\nState Menu Created\t\t" << this << std::endl;
}

void StateMenu::Init()
{
	this->m_fadeIn = std::make_unique<Transition>(m_data, "FadeIn", true);
	this->m_fadeOut = std::make_unique<Transition>(m_data, "FadeOut", true);

	this->m_currentLevel = std::make_unique<CurrentLevel>(0);

	this->m_map = std::make_unique<Map>(m_data, m_currentLevel->GetLevel(), m_currentLevel->GetLevelColor());

	for (auto startPosition : m_currentLevel->GetAndroidsStartPositions())
	{
		auto android = std::make_shared< AndroidDemo>(m_data, startPosition, m_map->GetPath(), m_currentLevel->GetLevel());
		m_androids.push_back(android);
	}

	this->m_str_start.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_start.setCharacterSize(TILE_SIZE);
	this->m_str_start.setString(sf::String("SPACEBAR TO START"));
	this->m_str_start.setFillColor(sf::Color(255, 255, 000, 255));
	this->m_str_start.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_str_start.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) + static_cast<int>(1.5 * TILE_SIZE)));

	this->m_str_how_to1.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_how_to1.setCharacterSize(static_cast <int>(0.8 * TILE_SIZE));
	this->m_str_how_to1.setString(sf::String("ARROWS TO MOVE"));
	this->m_str_how_to1.setFillColor(sf::Color(255, 000, 000, 255));
	this->m_str_how_to1.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_str_how_to1.getGlobalBounds().width / 2), this->m_str_start.getPosition().y + static_cast<int>(TILE_SIZE * 1.5)));

	this->m_str_how_to2 = this->m_str_how_to1;
	this->m_str_how_to2.setCharacterSize(static_cast <int>(0.6 * TILE_SIZE));
	this->m_str_how_to2.setString(sf::String("SPACEBAR TO DIG"));
	this->m_str_how_to2.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_str_how_to2.getGlobalBounds().width / 2), this->m_str_how_to1.getPosition().y + static_cast<int>(this->m_str_how_to1.getCharacterSize() * 1.5)));

	this->m_str_toggle_fullscreen = this->m_str_how_to2;
	this->m_str_toggle_fullscreen.setCharacterSize(static_cast<int>(0.4 * TILE_SIZE));
	this->m_str_toggle_fullscreen.setString(sf::String("F TO TOGGLE FULLSCREEN"));
	this->m_str_toggle_fullscreen.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_str_toggle_fullscreen.getGlobalBounds().width / 2), this->m_str_how_to2.getPosition().y + static_cast<int>(this->m_str_how_to2.getCharacterSize() * 1.5)));
	this->m_str_demo_countdown = this->m_str_how_to1;
	this->m_str_demo_countdown.setString(sf::String("Demo within 15 seconds"));
	this->m_str_demo_countdown.setFillColor(sf::Color(255, 255, 000, 255));
	this->m_str_demo_countdown.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_str_demo_countdown.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) + static_cast <int>(6.5 * TILE_SIZE)));

	this->m_str_credits1.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_credits1.setCharacterSize(TILE_SIZE / 2);
	this->m_str_credits1.setString(sf::String("From the Original game by William Hennebois (1985)    Infogrames"));
	this->m_str_credits1.setFillColor(sf::Color(255, 255, 255, 255));
	this->m_str_credits1.setPosition(0, TILE_SIZE * 22 + TILE_SIZE / 2);

	this->m_str_credits2 = this->m_str_credits1;
	this->m_str_credits2.setString(sf::String("For Gamecodeur Game Jam #24 on itch.io         www.gamecodeur.fr"));
	m_str_credits2.setPosition(0, TILE_SIZE * 24 - TILE_SIZE / 2);

	this->m_fadeIn->Start();
}

void StateMenu::ToggleFullscren()
{
	{
		this->Fullscreen = !this->Fullscreen;
		this->m_data->window.close();
		this->m_data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Androides 2020", this->Fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
		this->m_data->window.setFramerateLimit(60);
	}
}

void StateMenu::SetTimer(int p_levelTimer)
{
	std::string tmp = std::to_string(p_levelTimer);
	int strLen = tmp.length();

	int numberOfZero = 2 - strLen;

	std::string timer = std::string(numberOfZero, '0').append(tmp);

	sf::String demoWithin = "Demo within ";
	sf::String seconds = " seconds";

	auto final = demoWithin + timer + seconds;

	m_str_demo_countdown.setString(sf::String(final));
}

void StateMenu::Timer(float dt)
{
	if (m_demoTimer > 0)
	{
		m_dtTotal += dt;
		if (m_dtTotal >= 1)
		{
			m_demoTimer -= 1;
			this->SetTimer(m_demoTimer);
			m_dtTotal = 0.0f;
		}
	}
}

void StateMenu::HandleInput()
{
	sf::Event event;

	while (this->m_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->m_data->window.close();
		}

		if (event.type == sf::Event::Resized) {
			auto m_window_width = event.size.width;
			auto m_window_height = event.size.height;
			float new_width = ASPECT_RATIO * m_window_height;
			float new_height = m_window_width / ASPECT_RATIO;
			float offset_width = (m_window_width - new_width) / 2.0f;
			float offset_height = (m_window_height - new_height) / 2.0f;
			sf::View view = m_data->window.getDefaultView();
			if (m_window_width >= ASPECT_RATIO * m_window_height) {
				view.setViewport(sf::FloatRect(offset_width / m_window_width, 0.0, new_width / m_window_width, 1.0));
			}
			else {
				view.setViewport(sf::FloatRect(0.0, offset_height / m_window_height, 1.0, new_height / m_window_height));
			}

			m_data->window.setView(view);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		ToggleFullscren();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !this->m_fadeIn->IsInProgress() && !this->m_fadeOut->IsInProgress() && !this->m_isStateOver)
	{
		this->m_fadeOut->Start();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->m_data->window.close();
	}
}

void StateMenu::Update(float dt)
{
	Timer(dt);

	if (m_demoTimer == 0 && !this->m_isStateOver)
	{
		m_GotoDemo = true;
		this->m_fadeOut->Start();
	}

	if (this->m_fadeIn->IsInProgress())
	{
		this->m_fadeIn->Update(dt);
	}

	for (auto const& android : m_androids)
	{
		android->Update(dt);
	}

	if (this->m_fadeOut->IsInProgress())
	{
		this->m_fadeOut->Update(dt);
	}

	if (this->m_fadeOut->IsCompleted() && !this->m_isStateOver)
	{
		this->m_isStateOver = true;

		if (m_GotoDemo == true)
		{
			this->m_data->stateMachine.AddState(StateRef(new StateDemo(m_data)), true);
		}
		else
		{
			this->m_data->stateMachine.AddState(StateRef(new StatePlay(m_data)), true);
		}
	}
}

void StateMenu::Draw(float dt)
{
	this->m_data->window.clear();

	for (auto const& android : m_androids)
	{
		android->Draw();
	}

	this->m_map->Draw();

	this->m_data->window.draw(m_str_start);
	this->m_data->window.draw(m_str_how_to1);
	this->m_data->window.draw(m_str_how_to2);
	this->m_data->window.draw(m_str_toggle_fullscreen);
	this->m_data->window.draw(m_str_demo_countdown);

	this->m_data->window.draw(m_str_credits1);
	this->m_data->window.draw(m_str_credits2);

	this->m_fadeIn->Draw();
	this->m_fadeOut->Draw();

	this->m_data->window.display();
}