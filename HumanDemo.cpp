#include "HumanDemo.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

HumanDemo::HumanDemo(GameDataRef p_data, sf::Vector2f p_startPosition, std::vector<std::string>& p_path,
	std::unique_ptr<std::vector<std::string>>& p_level)
	: Sprite(p_data, p_startPosition, p_path, p_level)
{
}

HumanDemo::~HumanDemo()
{
}

void HumanDemo::NextMotion()
{
	if (!m_step1 && m_presentPosition.x < 30 * 16.0f)
	{
		m_nextPosition.x = m_presentPosition.x + 16.0f;
	}
	if (m_presentPosition.x >= 30 * 16.0f)
	{
		m_step1 = true;
	}

	if (m_step1 && !m_step2 && m_presentPosition.x > 3 * 16.0f)
	{
		m_nextPosition.x = m_presentPosition.x - 16.0f;
	}
	if (m_presentPosition.x <= 3 * 16.0f)
	{
		m_step2 = true;
	}

	if (m_step1 && m_step2 && !m_step3 && m_presentPosition.y > 13 * 8.0f)
	{
		m_nextPosition.y = m_presentPosition.y - 8.0f;
	}
	if (m_presentPosition.y <= 13 * 8.0f)
	{
		m_step3 = true;
	}

	if (m_step1 && m_step2 && m_step3 && !m_step4 && m_presentPosition.x <= 11 * 16.0f)
	{
		m_nextPosition.x = m_presentPosition.x + 16.0f;
		if (m_presentPosition.x >= 11 * 16.0f)
		{
			m_step4 = true;
		}
	}

	if (m_step4 && !m_step5)
	{
		m_spriteShape.setTextureRect(this->m_data->assetManager.GetRect("dig"));
		m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x + 32) / 16] = ' ';
		m_step5 = true;
	}

	if (m_step5 && !m_step6 && m_presentPosition.x >= 4 * 16.0f)
	{
		m_nextPosition.x = m_presentPosition.x - 16.0f;
		if (m_presentPosition.x <= 4 * 16.0f)
		{
			m_step6 = true;
		}
	}

	if (m_step6 && !m_step7 && m_presentPosition.y > 3 * 8.0f)
	{
		m_nextPosition.y = m_presentPosition.y - 8.0f;
	}
	if (m_presentPosition.y <= 3 * 8.0f)
	{
		m_step7 = true;
	}

	if (m_step7 && !m_step8 && m_presentPosition.x <= 7 * 16.0f)
	{
		m_nextPosition.x = m_presentPosition.x + 16.0f;
		if (m_presentPosition.x >= 7 * 16.0f)
		{
			m_step8 = true;
		}
	}

	if (m_step8 && !m_step9)
	{
		m_spriteShape.setTextureRect(this->m_data->assetManager.GetRect("dig"));
		m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x + 32) / 16] = ' ';
		m_step9 = true;
	}

	if (m_step9 && !m_step10)
	{
		m_nextPosition.x = m_presentPosition.x + 32.0f;
		m_step10 = true;
	}

	if (m_presentPosition.x == 144 && m_presentPosition.y == 72)
	{
		m_endDemo = true;
	}
}

bool HumanDemo::EndDemo() const
{
	return m_endDemo;
}

void HumanDemo::Update(float p_deltaTime)
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

sf::Vector2f* HumanDemo::GetHumanPosition()
{
	return &m_presentPosition;
}
