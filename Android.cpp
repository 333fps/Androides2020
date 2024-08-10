#include "Android.h"

Android::Android(GameDataRef p_data, const sf::Vector2f& p_startPosition, std::vector<std::string>& p_path,
	std::unique_ptr<std::vector<std::string>>& p_level, const sf::Vector2f* p_humanPostion, float p_dtOffset)
	: Sprite(p_data, p_startPosition, p_path, p_level, p_humanPostion, p_dtOffset),
	  m_target(*p_humanPostion)
{
	m_dtMax = 0.12f + p_dtOffset;
}

Android::~Android()
{
}

void Android::NextMotion()
{
	// DOWN
	if (m_target.y > m_presentPosition.y)
	{
		// DOWN LEFT
		if (m_target.x > m_presentPosition.x)
		{
			if (m_path[((size_t)m_presentPosition.y + 8) / 8][(size_t)m_presentPosition.x / 16] != 'w')
			{
				m_nextPosition.x = m_presentPosition.x + 16.0f;
			}
			if (m_path[((size_t)m_presentPosition.y + 8) / 8][(size_t)m_presentPosition.x / 16] == 'w')
			{
				m_nextPosition.y = m_presentPosition.y + 8.0f;
			}
		}
		// DOWN RIGHT
		if (m_target.x < m_presentPosition.x)
		{
			if (m_path[((size_t)m_presentPosition.y + 8) / 8][(size_t)m_presentPosition.x / 16] != 'w')
			{
				m_nextPosition.x = m_presentPosition.x - 16.0f;
			}
			if (m_path[((size_t)m_presentPosition.y + 8) / 8][(size_t)m_presentPosition.x / 16] == 'w')
			{
				m_nextPosition.y = m_presentPosition.y + 8.0f;
			}
		}
	}

	// UP
	if (m_target.y < m_presentPosition.y)
	{
		// UP RIGHT
		if (m_target.x > m_presentPosition.x)
		{
			if (m_path[((size_t)m_presentPosition.y - 8) / 8][(size_t)m_presentPosition.x / 16] != 'w')
			{
				m_nextPosition.x = m_presentPosition.x + 16.0f;
			}
			if (m_path[((size_t)m_presentPosition.y - 8) / 8][(size_t)m_presentPosition.x / 16] == 'w')
			{
				m_nextPosition.y = m_presentPosition.y - 8.0f;
			}
		}
		// UP LEFT
		if (m_target.x < m_presentPosition.x)
		{
			if (m_path[((size_t)m_presentPosition.y - 8) / 8][(size_t)m_presentPosition.x / 16] != 'w')
			{
				m_nextPosition.x = m_presentPosition.x - 16.0f;
			}
			if (m_path[((size_t)m_presentPosition.y - 8) / 8][(size_t)m_presentPosition.x / 16] == 'w')
			{
				m_nextPosition.y = m_presentPosition.y - 8.0f;
			}
		}
	}

	// LEFT
	if (m_target.x <= m_presentPosition.x && m_target.y == m_presentPosition.y)
	{
		m_nextPosition.x = m_presentPosition.x - 16.0f;
	}

	// RIGHT
	if (m_target.x >= m_presentPosition.x && m_target.y == m_presentPosition.y)
	{
		m_nextPosition.x = m_presentPosition.x + 16.0f;
	}

	// up
	if (m_target.x == m_presentPosition.x && m_target.y <= m_presentPosition.y)
	{
		m_nextPosition.y = m_presentPosition.y - 8.0f;
	}

	// down
	if (m_target.x == m_presentPosition.x && m_target.y >= m_presentPosition.y)
	{
		m_nextPosition.y = m_presentPosition.y + 8.0f;
	}
}

void Android::UpdateCatch()
{
	if (m_target.x == m_nextPosition.x && m_target.y == m_nextPosition.y)
	{
		m_catch = true;
	}
}

bool& Android::isCatching()
{
	return m_catch;
}

void Android::Update(float p_deltaTime)

{
	m_totalTime += p_deltaTime;
	m_presentPosition = m_spriteShape.getPosition();

	// In hole
	if (m_level[((size_t)m_presentPosition.y) / 16][((size_t)m_presentPosition.x) / 16] == 'x')
	{
		if (m_level[((size_t)m_presentPosition.y) / 16][((size_t)m_presentPosition.x + 16) / 16] == '@' && m_level[((size_t)m_presentPosition.y) / 16][((size_t)m_presentPosition.x - 16) / 16] == '@')
		{
			if (m_presentPosition.y < 328)
			{
				if (m_level[((size_t)m_presentPosition.y + 16) / 16][((size_t)m_presentPosition.x) / 16] != ' ')
				{
					m_level[((size_t)m_presentPosition.y) / 16][((size_t)m_presentPosition.x) / 16] = 'T';
				}
			}
			else
			{
				m_level[((size_t)m_presentPosition.y) / 16][((size_t)m_presentPosition.x) / 16] = 'T';
			}
		}
	}

	UpdateCatch();

	if (m_totalTime > m_dtMax)
	{
		if (!m_isFalling)
		{
			if (!m_isInWall)
				NextMotion();
			if (!IsInBounds())
				m_nextPosition = m_presentPosition;
			if (!IsOnPath())
				m_nextPosition = m_presentPosition;
			if (m_isInWall && m_presentPosition.y > 8.0f)
				m_nextPosition.y = m_presentPosition.y - 8.0f;
		}
		else
		{
			m_nextPosition.y = m_presentPosition.y + 8.0f;
		}
		if (m_catch)
		{
			m_nextPosition.x = m_target.x;
			m_nextPosition.y = m_target.y;
		}

		UpdateStatus();

		m_totalTime = 0;
		m_spriteShape.setPosition(m_nextPosition);
	}
}
