#include "Sprite.h"
#include "DEFINITIONS.h"

Sprite::Sprite(GameDataRef p_data, const sf::Vector2f& p_startPosition, std::vector<std::string>& p_path,
	std::unique_ptr<std::vector<std::string>>& p_level, const sf::Vector2f* p_humanPostion, float p_dtOffset)
	: m_data(p_data),
	  m_level(*p_level),
	  m_path(p_path),
	  m_startPosition(p_startPosition)
{
	(void)p_dtOffset;
	(void)p_humanPostion;
	Init();
	m_dtMax = 0.15f;

	m_spriteShape.setColor(sf::Color::Red);
}

Sprite::Sprite(GameDataRef p_data, const sf::Vector2f& p_startPosition, std::vector<std::string>& p_path,
	std::unique_ptr<std::vector<std::string>>& p_level)
	: m_data(p_data),
	  m_level(*p_level),
	  m_path(p_path),
	  m_startPosition(p_startPosition)
{
	Init();
	m_dtMax = 0.1f;
	m_spriteShape.setColor(sf::Color::Yellow);
}

Sprite::~Sprite()
{
}

void Sprite::Init()
{
	m_spriteShape.setOrigin(sf::Vector2f(0.0f, 8.0f));
	m_spriteShape.setPosition(m_startPosition);
	m_nextPosition = m_spriteShape.getPosition();
	m_isFalling = false;

	m_spriteShape.setTexture(this->m_data->assetManager.GetTexture("spritesheet"));

	m_animRun.push_back(this->m_data->assetManager.GetRect("run_1"));
	m_animRun.push_back(this->m_data->assetManager.GetRect("run_2"));
	m_animRun.push_back(this->m_data->assetManager.GetRect("run_3"));
	m_animRun.push_back(this->m_data->assetManager.GetRect("run_4"));

	m_animRope.push_back(this->m_data->assetManager.GetRect("rope_1"));
	m_animRope.push_back(this->m_data->assetManager.GetRect("rope_2"));
	m_animRope.push_back(this->m_data->assetManager.GetRect("rope_3"));
	m_animRope.push_back(this->m_data->assetManager.GetRect("rope_4"));

	m_spriteShape.setTextureRect(this->m_data->assetManager.GetRect("wait"));
}

void Sprite::CheckDirection()
{
	auto m_previousDirection = m_direction;

	if (m_nextPosition.x > m_presentPosition.x)
	{
		m_direction = true;
	}
	else
	{
		m_direction = false;
	}

	if (m_nextPosition.x == m_presentPosition.x)
	{
		m_direction = m_previousDirection;
	}
}

sf::IntRect Sprite::NextRunFrame()
{
	if (m_runFrame < 3)
	{
		m_runFrame++;
	}
	else
	{
		m_runFrame = 0;
	}

	return m_animRun[m_runFrame];
}

sf::IntRect Sprite::NextRopeFrame()
{
	if (m_nextPosition.x != m_presentPosition.x)
	{
		if (m_ropeFrame < 3)
		{
			m_ropeFrame++;
		}
		else
		{
			m_ropeFrame = 0;
		}
	}

	return m_animRope[m_ropeFrame];
}

bool Sprite::IsInBounds() const
{
	if (m_nextPosition.x < 0 || m_nextPosition.x > 624 || m_nextPosition.y < 8 || m_nextPosition.y > 344)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Sprite::IsOnPath()
{
	if (m_path[(size_t)m_nextPosition.y / 8][(size_t)m_nextPosition.x / 16] == 'f' && m_nextPosition.y < m_presentPosition.y)
	{
		return false;
	}

	if (m_path[(size_t)m_nextPosition.y / 8][(size_t)m_nextPosition.x / 16] == 'w' || m_path[(size_t)m_nextPosition.y / 8][(size_t)m_nextPosition.x / 16] == 'f')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Sprite::UpdateStatus()
{
	CheckDirection();
	IsFalling();
	IsInWall();
	IsOnRope();
	IsOnLadder();
	IsRunning();
	IsWaiting();

	UpdateTexture();
}

void Sprite::UpdateTexture()
{
	if (m_isFalling)
	{
		if (!m_direction)
		{
			m_spriteShape.setScale(1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(0.0f, 8.0f));
		}
		else
		{
			// m_spriteShape.setScale(-1.0f, 1.0f);
			// m_spriteShape.setOrigin(sf::Vector2f(16.0f, 8.0f));
		}
		m_spriteShape.setTextureRect(this->m_data->assetManager.GetRect("falling"));
	}

	if (m_isRunning)
	{
		if (!m_direction)
		{
			m_spriteShape.setScale(1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(0.0f, 8.0f));
		}
		else
		{
			m_spriteShape.setScale(-1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(16.0f, 8.0f));
		}
		m_spriteShape.setTextureRect(NextRunFrame());
	}

	if (m_isOnLadder)
	{
		if (static_cast<int>(m_nextPosition.y) % 16 == 0)
		{
			m_spriteShape.setScale(1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(0.0f, 8.0f));
		}
		else
		{
			m_spriteShape.setScale(-1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(16.0f, 8.0f));
		}

		m_spriteShape.setTextureRect(this->m_data->assetManager.GetRect("ladder"));
	}

	if (m_isOnRope)
	{
		if (!m_direction)
		{
			m_spriteShape.setScale(1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(0.0f, 0.0f));
		}
		else
		{
			m_spriteShape.setScale(-1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(16.0f, 0.0f));
		}
		m_spriteShape.setTextureRect(NextRopeFrame());
	}

	if (m_isWaiting || m_isInWall)
	{
		m_spriteShape.setTextureRect(this->m_data->assetManager.GetRect("wait"));
	}

	if (m_isDigging)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_spriteShape.setScale(1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(0.0f, 8.0f));
		}
		else
		{
			m_spriteShape.setScale(-1.0f, 1.0f);
			m_spriteShape.setOrigin(sf::Vector2f(16.0f, 8.0f));
		}
		m_spriteShape.setTextureRect(this->m_data->assetManager.GetRect("dig"));
	}
}

void Sprite::IsFalling()
{
	if (m_path[(size_t)m_nextPosition.y / 8][(size_t)m_nextPosition.x / 16] == 'f' || m_path[(size_t)m_nextPosition.y / 8][(size_t)m_nextPosition.x / 16] == 'x' || m_path[(size_t)m_nextPosition.y / 8][(size_t)m_nextPosition.x / 16] == ' ')
	{
		m_isFalling = true;
	}
	else
	{
		m_isFalling = false;
	}
}

void Sprite::IsInWall()
{
	if (m_path[(size_t)m_nextPosition.y / 8][(size_t)m_nextPosition.x / 16] == '@' && m_presentPosition.y >= 16)
	{
		m_isInWall = true;
	}
	else
	{
		m_isInWall = false;
	}
}

void Sprite::IsRunning()
{
	if (IsOnPath() && !m_isOnRope && m_isOnLadder == false && !m_isFalling && m_presentPosition.x != m_nextPosition.x)
	{
		m_isRunning = true;
	}
	else
	{
		m_isRunning = false;
	}
}

void Sprite::IsWaiting()
{
	if (IsOnPath() && m_presentPosition.x == m_nextPosition.x && !m_isFalling && m_isOnLadder == false && m_isOnRope == false && m_isRunning == false)
	{
		m_spriteShape.setOrigin(sf::Vector2f(0.0f, 8.0f));
		m_spriteShape.setScale(1.0f, 1.0f);

		m_isWaiting = true;
	}
	else
	{
		m_isWaiting = false;
	}
}

void Sprite::IsOnRope()
{
	if (m_level[((size_t)m_presentPosition.y) / 16][((size_t)m_presentPosition.x) / 16] == '_' && m_isFalling == false && IsOnPath())
	{
		m_isOnRope = true;
	}
	else
	{
		m_isOnRope = false;
	}
	if (m_isOnRope)
	{
		if (m_path[((size_t)m_nextPosition.y + 8) / 8][(size_t)m_nextPosition.x / 16] == '@')
		{
			m_isOnRope = false;
		}
	}
}

void Sprite::IsOnLadder()
{
	if (m_level[((size_t)m_presentPosition.y) / 16][((size_t)m_presentPosition.x) / 16] == 'H' && m_isFalling == false)
	{
		m_isOnLadder = true;
	}
	else
	{
		m_isOnLadder = false;
	}
}

void Sprite::Draw()
{
	m_spriteShapeScaled = m_spriteShape;

	m_spriteShapeScaled.setPosition(SCALE_FACTOR * m_spriteShape.getPosition());
	m_spriteShapeScaled.setScale(m_spriteShape.getScale() * SCALE_FACTOR);

	m_data->window.draw(m_spriteShapeScaled);
}
