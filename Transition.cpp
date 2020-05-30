#include "Transition.h"

Transition::Transition(GameDataRef p_data, std::string p_type, bool p_fullscreen) :
	m_data(p_data),
	m_fullScreen(p_fullscreen)
{
	//std::cout << "Transition Created\t\t" << this << std::endl;

	this->m_brickShape.setTexture(this->m_data->assetManager.GetTexture("spritesheet"));
	this->m_brickShape.setTextureRect(this->m_data->assetManager.GetRect("brick"));
	this->m_brickShape.setColor(sf::Color(0, 0, 255, 255));

	this->m_blackShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	this->m_blackShape.setFillColor(sf::Color(0, 0, 0, 255));

	if (p_type == "FadeIn")
	{
		m_type = 0;
	}
	else
	{
		m_type = 1;
	}

	if (m_fullScreen)
	{
		m_maxline = 25;
	}
	else
	{
		m_maxline = 22;
		for (size_t i = 0; i < 40; ++i)
		{
			for (size_t j = m_maxline; j < (25); ++j)
			{
				arr[i][j] = !m_type;
			}
		}
	}
}

void Transition::Update(float dt)
{
	if (this->m_isOver == false)
	{
		this->m_totalTime += dt;

		if (this->m_totalTime > TRANSTION_TIME)
		{
			if (m_iStart >= 1)
			{
				m_iStart = m_iStart - 1;
				m_jStart = m_jStart - 1;
			}

			for (size_t i = m_iStart; i < (40 - m_iStart); ++i)
			{
				for (size_t j = m_jStart; j < (m_maxline - m_jStart); ++j)
				{
					arr[i][j] = 1;
				}
			}

			if (m_iStart == 0)
			{
				this->m_isCompleted = true;
				this->m_isOver = true;
			}

			this->m_totalTime = 0;
		}
	}
	m_brickShapeScaled = m_brickShape;
	m_brickShapeScaled.setScale(m_brickShape.getScale() * SCALE_FACTOR);
}

void Transition::Draw()
{
	unsigned int i = 0;
	for (auto line : arr)
	{
		unsigned int j = 0;
		for (auto val : line)
		{
			if (val == m_type)
			{
				this->m_blackShape.setPosition(sf::Vector2f(i * (float)TILE_SIZE, j * (float)TILE_SIZE));
				this->m_brickShapeScaled.setPosition(sf::Vector2f(i * (float)TILE_SIZE, j * (float)TILE_SIZE));

				this->m_data->window.draw(m_blackShape);
				this->m_data->window.draw(m_brickShapeScaled);
			}
			++j;
		}
		++i;
	}
}

bool Transition::IsInProgress()
{
	if (!m_isOver && m_isStarted)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Transition::IsCompleted()
{
	if (m_isCompleted)
		return true;
	else
		return false;
}

void Transition::Start()
{
	m_isStarted = true;
	m_isOver = false;
}