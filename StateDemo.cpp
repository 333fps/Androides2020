#include "StateDemo.h"
#include "StateMenu.h"

#include "DEFINITIONS.h"

#include <iostream>
#include <memory>

StateDemo::StateDemo(GameDataRef p_data) : m_data(p_data)
{
	//std::cout << "\nState Play Created\t\t" << this << std::endl;
}

void StateDemo::ToggleFullscren()
{
	this->Fullscreen = !this->Fullscreen;
	this->m_data->window.close();
	this->m_data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Androides 2020", this->Fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	this->m_data->window.setFramerateLimit(60);
}

void StateDemo::Init()
{
	this->m_str_backToMenu1.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_backToMenu1.setCharacterSize(TILE_SIZE / 2);
	this->m_str_backToMenu1.setString(sf::String("DEMO"));
	this->m_str_backToMenu1.setFillColor(sf::Color(255, 255, 255, 255));
	this->m_str_backToMenu1.setPosition(SCREEN_WIDTH / 2 - m_str_backToMenu1.getGlobalBounds().width / 2, TILE_SIZE * 22 + TILE_SIZE / 2);

	this->m_str_backToMenu2 = this->m_str_backToMenu1;
	this->m_str_backToMenu2.setString(sf::String("PRESS ANY KEY TO GO BACK TO MENU"));
	this->m_str_backToMenu2.setPosition(SCREEN_WIDTH / 2 - m_str_backToMenu2.getGlobalBounds().width / 2, TILE_SIZE * 24 - TILE_SIZE / 2);

	this->Start();
}

void StateDemo::Start()
{
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

	m_currentLevel = std::make_unique<CurrentLevel>(1);

	m_map = std::make_unique<Map>(m_data, m_currentLevel->GetLevel(), m_currentLevel->GetLevelColor());

	m_human = std::make_shared<HumanDemo>(m_data, m_currentLevel->GetHumanStartPosition(), m_map->GetPath(), m_currentLevel->GetLevel());

	float dtoffset = 0;
	for (auto startPosition : m_currentLevel->GetAndroidsStartPositions())
	{
		auto android = std::make_shared<Android>(m_data, startPosition, m_map->GetPath(), m_currentLevel->GetLevel(), m_human->GetHumanPosition(), dtoffset);
		m_androids.push_back(android);
	}

	this->m_fadeIn->Start();
}

void StateDemo::HandleInput()
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

		if (sf::Event::KeyPressed == event.type && !sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			m_fadeOut->Start();
		}
	}
}

void StateDemo::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		ToggleFullscren();
	}

	if (m_human->EndDemo() && !m_fadeIn->IsInProgress() && !m_fadeOut->IsInProgress())
	{
		m_fadeOut->Start();
	}

	if (this->m_fadeIn->IsInProgress() && this->m_pause)
	{
		this->m_fadeIn->Update(dt);
	}

	if (this->m_fadeIn->IsCompleted() && this->m_pause)
	{
		this->m_pause = false;
	}

	m_map->Update();

	if (!m_pause)
	{
		m_map->Update();

		m_human->Update(dt);

		for (auto const& android : m_androids)
		{
			android->Update(dt);
		}
	}

	if (this->m_fadeOut->IsInProgress())
	{
		this->m_fadeOut->Update(dt);
	}

	if (this->m_fadeOut->IsCompleted())
	{
		this->m_data->stateMachine.AddState(StateRef(new StateMenu(m_data)), true);
	}
}

void StateDemo::Draw(float dt)
{
	this->m_data->window.clear();

	this->m_human->Draw();

	for (auto const& android : m_androids)
	{
		android->Draw();
	}

	this->m_map->Draw();
	//this->m_map->DrawPath();

	this->m_data->window.draw(m_str_backToMenu1);
	this->m_data->window.draw(m_str_backToMenu2);

	this->m_fadeIn->Draw();
	this->m_fadeOut->Draw();

	this->m_data->window.display();
}