#include "StateSplashScreen.h"
#include "StateMenu.h"
#include "DEFINITIONS.h"

StateSplash::StateSplash(GameDataRef p_data) :
	m_data(p_data)
{
	//std::cout << "State Splashscreen Created\t" << this << std::endl;
}

void StateSplash::ToggleFullscren()
{
	this->Fullscreen = !this->Fullscreen;
	this->m_data->window.close();
	this->m_data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Androides 2020", this->Fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	this->m_data->window.setFramerateLimit(60);
}

void StateSplash::Init()
{
	//Loading fonts
	this->m_data->assetManager.LoadFont("Microgramma", FONT_MICROGRAMMA);
	this->m_data->assetManager.LoadFont("Thomson", FONT_THOMSON);
	this->m_data->assetManager.LoadFont("LodeRunner", FONT_LODE_RUNNER);

	//Loading textures
	this->m_data->assetManager.LoadTexture("spritesheet", SPRITESHEET);

	//Set rects/
	this->m_data->assetManager.SetRect("wait", 0, 32, 16, 16);
	this->m_data->assetManager.SetRect("ladder", 48, 32, 16, 16);
	this->m_data->assetManager.SetRect("falling", 16, 32, 16, 16);
	this->m_data->assetManager.SetRect("run_1", 0, 0, 16, 16);
	this->m_data->assetManager.SetRect("run_2", 16, 0, 16, 16);
	this->m_data->assetManager.SetRect("run_3", 32, 0, 16, 16);
	this->m_data->assetManager.SetRect("run_4", 48, 0, 16, 16);
	this->m_data->assetManager.SetRect("rope_1", 0, 16, 16, 16);
	this->m_data->assetManager.SetRect("rope_2", 16, 16, 16, 16);
	this->m_data->assetManager.SetRect("rope_3", 32, 16, 16, 16);
	this->m_data->assetManager.SetRect("rope_4", 48, 16, 16, 16);
	this->m_data->assetManager.SetRect("dig", 32, 32, 16, 16);

	this->m_data->assetManager.SetRect("brick", 0, 48, 16, 16);

	//Sounds
	this->m_data->assetManager.LoadSound("beep", SOUND_BEEP);
	this->m_data->assetManager.LoadSound("hit", SOUND_HIT);
	this->m_data->assetManager.LoadSound("tick", SOUND_TICK);
	this->m_data->assetManager.LoadSound("win", SOUND_WIN);
	this->m_data->assetManager.LoadSound("bonus", SOUND_BONUS);
	this->m_data->assetManager.LoadSound("dig", SOUND_DIG);

	//Objects
	this->m_splashScreen = std::make_unique<SplashScreen>(m_data);
	this->m_fadeOut = std::make_unique<Transition>(m_data, "FadeOut", true);

	this->m_clock.restart(); // <- To allow time to load assets
}

void StateSplash::HandleInput()
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->m_data->window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			ToggleFullscren();
		}
	}
}

void StateSplash::Update(float dt)
{
	if (this->m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME && !this->m_fadeOut->IsInProgress() && !this->m_isStateOver)
	{
		this->m_fadeOut->Start();
	}

	if (this->m_fadeOut->IsInProgress())
	{
		this->m_fadeOut->Update(dt);
	}

	// Switch To Main Menu
	if (this->m_fadeOut->IsCompleted() && !this->m_isStateOver)
	{
		this->m_isStateOver = true; // to ensure this step is over and avoid calling next step twice.
		this->m_data->stateMachine.AddState(StateRef(new StateMenu(m_data)), true);
	}
}

void StateSplash::Draw(float dt)
{
	this->m_data->window.clear(COLOR_CYAN);

	this->m_splashScreen->Draw();
	this->m_fadeOut->Draw();

	this->m_data->window.display();
}