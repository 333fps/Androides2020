#include "Levels.h"

Levels::Levels(int p_levelNumber) : m_levelNumber{ p_levelNumber }
{
}

Levels::~Levels()
{
}

std::unique_ptr<std::vector<std::string>> Levels::GetLevel()
{
	switch (m_levelNumber)
	{
		case 0:
			m_level = m_level_000;
			break;
		case 1:
			m_level = m_level_001;
			break;
		case 2:
			m_level = m_level_002;
			break;
		case 3:
			m_level = m_level_003;
			break;
		case 4:
			m_level = m_level_004;
			break;
		case 5:
			m_level = m_level_005;
			break;
		case 6:
			m_level = m_level_006;
			break;
		case 7:
			m_level = m_level_007;
			break;
		case 8:
			m_level = m_level_008;
			break;
		case 9:
			m_level = m_level_009;
			break;
		case 10:
			m_level = m_level_010;
			break;
		case 99:
			m_level = m_level_099;
			break;
		default:
			break;
	}

	return std::make_unique<std::vector<std::string>>(m_level);
}
