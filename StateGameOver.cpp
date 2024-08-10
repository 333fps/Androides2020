#include "StateGameOver.h"

#include "DEFINITIONS.h"

#include <memory>

StateGameOver::StateGameOver(GameDataRef p_data, int p_finalScore, int p_finalLevel) : State{ p_data },
																					   m_data(p_data),
																					   m_finalScore(p_finalScore),
																					   m_finalLevel(p_finalLevel)

{
}

StateGameOver::~StateGameOver()
{
}

void StateGameOver::ToggleFullscren()
{
	this->Fullscreen = !this->Fullscreen;
	this->m_data->window.close();
	this->m_data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Androides 2020", this->Fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	this->m_data->window.setFramerateLimit(60);
}

void StateGameOver::Init()
{
	this->m_fadeIn = std::make_unique<Transition>(m_data, "FadeIn", false);
	this->m_fadeOut = std::make_unique<Transition>(m_data, "FadeOut", true);

	this->m_currentLevel = std::make_unique<CurrentLevel>(99);

	this->m_map = std::make_unique<Map>(m_data, m_currentLevel->GetLevel(), m_currentLevel->GetLevelColor());

	for (auto startPosition : m_currentLevel->GetAndroidsStartPositions())
	{
		auto android = std::make_shared<AndroidDemo>(m_data, startPosition, m_map->GetPath(), m_currentLevel->GetLevel());
		m_androids.push_back(android);
	}

	this->m_str_finalScore.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_finalScore.setCharacterSize(TILE_SIZE);
	this->m_str_finalScore.setString(sf::String("SCORE"));
	this->m_str_finalScore.setFillColor(sf::Color(255, 255, 000, 255));
	this->m_str_finalScore.setPosition(TILE_SIZE * 2, TILE_SIZE * 10);

	this->m_str_valFinalScore.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_valFinalScore.setCharacterSize(TILE_SIZE);
	this->m_str_valFinalScore.setString(sf::String("SCORE"));
	this->m_str_valFinalScore.setFillColor(sf::Color(255, 000, 000, 255));
	this->m_str_valFinalScore.setPosition(TILE_SIZE * 9, TILE_SIZE * 10);

	this->m_str_finalLevel.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_finalLevel.setCharacterSize(TILE_SIZE);
	this->m_str_finalLevel.setString(sf::String("LEVEL"));
	this->m_str_finalLevel.setFillColor(sf::Color(255, 255, 000, 255));
	this->m_str_finalLevel.setPosition(TILE_SIZE * 2, TILE_SIZE * 12);

	this->m_str_valFinalLevel.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_valFinalLevel.setCharacterSize(TILE_SIZE);
	this->m_str_valFinalLevel.setString(sf::String("LEVEL"));
	this->m_str_valFinalLevel.setFillColor(sf::Color(255, 000, 000, 255));
	this->m_str_valFinalLevel.setPosition(TILE_SIZE * 9, TILE_SIZE * 12);

	this->m_str_credits1.setFont(this->m_data->assetManager.GetFont("LodeRunner"));
	this->m_str_credits1.setCharacterSize(TILE_SIZE / 2);
	this->m_str_credits1.setString(sf::String("From the Original game by William Hennebois (1985)    Infogrames"));
	this->m_str_credits1.setFillColor(sf::Color(255, 255, 255, 255));
	this->m_str_credits1.setPosition(0, TILE_SIZE * 22 + TILE_SIZE / 2);

	this->m_str_credits2 = this->m_str_credits1;
	this->m_str_credits2.setString(sf::String("For Gamecodeur Game Jam #24 on itch.io         www.gamecodeur.fr"));
	m_str_credits2.setPosition(0, TILE_SIZE * 24 - TILE_SIZE / 2);

	Score();
	Level();

	this->m_fadeIn->Start();
}

void StateGameOver::Score()
{
	std::string tmp = std::to_string(m_finalScore);
	auto strLen = tmp.length();

	auto numberOfZero = 6 - strLen;

	std::string final = std::string(numberOfZero, '0').append(tmp);

	m_str_valFinalScore.setString(sf::String(final));
}

void StateGameOver::Level()
{
	std::string tmp = std::to_string(m_finalLevel);
	auto strLen = tmp.length();

	auto numberOfZero = 3 - strLen;

	std::string level = std::string(numberOfZero, '0').append(tmp);

	std::string endStr = "/010";

	auto final = level + endStr;
	m_str_valFinalLevel.setString(sf::String(final));
}

void StateGameOver::HandleInput()
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			ToggleFullscren();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_fadeIn->IsInProgress() && !m_fadeOut->IsInProgress())
	{
		m_fadeOut->Start();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_fadeOut->Start();
	}
}

void StateGameOver::Update(float dt)
{
	if (this->m_fadeIn->IsInProgress())
	{
		this->m_fadeIn->Update(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_fadeIn->IsInProgress() && !m_fadeOut->IsInProgress())
	{
		m_fadeOut->Start();
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
		this->m_data->stateMachine.AddState(StateRef(new StateMenu(m_data)), true);
	}
}

void StateGameOver::Draw(float dt)
{
	(void)dt;
	this->m_data->window.clear();

	for (auto const& android : m_androids)
	{
		android->Draw();
	}

	this->m_map->Draw();
	// this->m_map->DrawPath();

	this->m_data->window.draw(m_str_finalScore);
	this->m_data->window.draw(m_str_finalLevel);

	this->m_data->window.draw(m_str_valFinalScore);
	this->m_data->window.draw(m_str_valFinalLevel);

	this->m_data->window.draw(m_str_credits1);
	this->m_data->window.draw(m_str_credits2);

	this->m_fadeIn->Draw();
	this->m_fadeOut->Draw();

	this->m_data->window.display();
}
