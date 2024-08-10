#ifndef _SPLASH_SCREEN_H_
#define _SPLASH_SCREEN_H_

#include <SFML/Graphics.hpp>

#include "GameEngine.h"

class SplashScreen
{
public:
	SplashScreen(GameDataRef p_data);
	~SplashScreen();

private:
	GameDataRef m_data;

	sf::RectangleShape m_shape_machineName;

	sf::Text m_txt_machineName;
	sf::Text m_txt_ThomsonBrand;
	sf::Text m_txt_version;
	sf::Text m_txt_date;
	sf::Text m_txt_ram;

	sf::RectangleShape m_shape_separator1;
	sf::RectangleShape m_shape_separator2;
	sf::RectangleShape m_shape_separator3;

	sf::RectangleShape m_opticalPenBox1;
	sf::RectangleShape m_opticalPenBox2;
	sf::RectangleShape m_opticalPenBox3;
	sf::RectangleShape m_opticalPenBox4;
	sf::RectangleShape m_opticalPenBox5;
	sf::RectangleShape m_opticalPenBox6;
	sf::RectangleShape m_opticalPenBox7;
	sf::RectangleShape m_opticalPenBox8;

	sf::Text m_txt_Str1;
	sf::Text m_txt_Str2;
	sf::Text m_txt_Str3;
	sf::Text m_txt_Str4;
	sf::Text m_txt_Str5;
	sf::Text m_txt_Str6;
	sf::Text m_txt_Str7;
	sf::Text m_txt_Str8;

private:
	std::string getLocalDate();

public:
	void Draw();
};

#endif // !_SPLASH_SCREEN_H_
