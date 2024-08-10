#include "Human.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

Human::Human(GameDataRef p_data, sf::Vector2f p_startPosition, std::vector<std::string>& p_path,
	std::unique_ptr<std::vector<std::string>>& p_level)
	: Sprite(p_data, p_startPosition, p_path, p_level)
{
}

Human::~Human()
{
}

void Human::NextMotion()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_nextPosition.x = m_presentPosition.x - 16.0f;
		m_nextPosition.y = m_presentPosition.y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_nextPosition.x = m_presentPosition.x + 16.0f;
		m_nextPosition.y = m_presentPosition.y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_nextPosition.x = m_presentPosition.x;
		m_nextPosition.y = m_presentPosition.y - 8.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_nextPosition.x = m_presentPosition.x;
		m_nextPosition.y = m_presentPosition.y + 8.0f;
	}

	// DIG
	m_isDigging = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x - 16) / 16] == '@')
		{
			m_isDigging = true;
			if (m_presentPosition.y < (344 - 8) && m_presentPosition.x >= 16)
			{
				if (m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x - 16) / 16] == '@')
				{
					m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x - 16) / 16] = 'X';
				}
			}
		}
		m_nextPosition = m_presentPosition;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x + 16) / 16] == '@')
		{
			m_isDigging = true;
			if (m_presentPosition.y < (344 - 8))
			{
				if (m_presentPosition.y < (344 - 8) && m_presentPosition.x < (40 * 16))
				{
					if (m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x + 16) / 16] == '@')
					{
						m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x + 16) / 16] = 'X';
					}
				}
			}
		}
		m_nextPosition = m_presentPosition;
	}
}

void Human::Update(float p_deltaTime)
{
	m_totalTime += p_deltaTime;

	if (m_totalTime > m_dtMax)
	{
		m_presentPosition = m_spriteShape.getPosition();

		if (!m_isFalling)
		{
			if (!m_isInWall)
				NextMotion();
			if (!IsInBounds())
				m_nextPosition = m_presentPosition;
			if (!IsOnPath())
				m_nextPosition = m_presentPosition;
			if (m_isInWall && m_presentPosition.y > 8.0f)
			{
				m_nextPosition.y = m_presentPosition.y - 8.0f;
			}
		}
		else
		{
			m_nextPosition.y = m_presentPosition.y + 8.0f;
		}

		if (m_level[((size_t)m_nextPosition.y) / 16][((size_t)m_nextPosition.x) / 16] == '*')
		{
			m_level[((size_t)m_nextPosition.y) / 16][((size_t)m_nextPosition.x) / 16] = ' ';
		}

		UpdateStatus();

		m_totalTime = 0;
	}
	m_spriteShape.setPosition(m_nextPosition);
}

sf::Vector2f* Human::GetHumanPosition()
{
	return &m_nextPosition;
}

bool& Human::isDigging()
{
	return m_isDigging;
}
