#define _CRT_SECURE_NO_WARNINGS

#include "SplashScreen.h"
#include "DEFINITIONS.h"

#include <ctime>
#include <string>

SplashScreen::SplashScreen(GameDataRef p_data) :
	m_data(p_data)
{
	//std::cout << "Splashscreen Created\t\t" << this << std::endl;

	// Rectangle Machine name
	this->m_shape_machineName.setFillColor(COLOR_STONE_BLUE);
	this->m_shape_machineName.setSize(sf::Vector2f(SCREEN_WIDTH - 0.05 * SCREEN_WIDTH, 0.32f * SCREEN_HEIGHT));
	this->m_shape_machineName.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_shape_machineName.getGlobalBounds().width / 2), SCREEN_WIDTH / 2 - m_shape_machineName.getGlobalBounds().width / 2));

	auto xPos = m_shape_machineName.getPosition().x;
	auto xOffset = m_shape_machineName.getSize().x;

	// Machine name
	this->m_txt_machineName.setFont(this->m_data->assetManager.GetFont("Microgramma"));
	this->m_txt_machineName.setString("ANDROIDES");
	this->m_txt_machineName.setFillColor(sf::Color::Transparent);
	this->m_txt_machineName.setCharacterSize(static_cast<int>(0.5f * m_shape_machineName.getGlobalBounds().height));
	this->m_txt_machineName.setOrigin(sf::Vector2f(m_txt_machineName.getGlobalBounds().left + m_txt_machineName.getGlobalBounds().width / 2, m_txt_machineName.getGlobalBounds().top + m_txt_machineName.getGlobalBounds().height / 2));
	this->m_txt_machineName.setPosition(sf::Vector2f(m_shape_machineName.getGlobalBounds().width / 2, m_shape_machineName.getGlobalBounds().height / 2));
	this->m_txt_machineName.setOutlineColor(sf::Color::White);
	this->m_txt_machineName.setOutlineThickness(1.0f);
	//this->m_txt_machineName.setLetterSpacing(1.5f);

	// Version
	this->m_txt_version.setFont(this->m_data->assetManager.GetFont("Microgramma"));
	this->m_txt_version.setString(VERSION_NUMBER);
	this->m_txt_version.setFillColor(sf::Color::White);
	this->m_txt_version.setCharacterSize(10);
	this->m_txt_version.setOrigin(sf::Vector2f(m_txt_version.getGlobalBounds().width, 0.0f));
	this->m_txt_version.setPosition(sf::Vector2f(m_shape_machineName.getGlobalBounds().width, m_shape_machineName.getGlobalBounds().height));
	//this->m_txt_version.setLetterSpacing(2.0f); <-- SFML 2.5

	// Brand
	this->m_txt_ThomsonBrand.setFont(this->m_data->assetManager.GetFont("Microgramma"));
	this->m_txt_ThomsonBrand.setString("333fps");
	this->m_txt_ThomsonBrand.setFillColor(sf::Color::Black);
	this->m_txt_ThomsonBrand.setCharacterSize(20);
	this->m_txt_ThomsonBrand.setOrigin(sf::Vector2f(m_txt_ThomsonBrand.getGlobalBounds().width, 0.0f));
	this->m_txt_ThomsonBrand.setPosition(sf::Vector2f(m_shape_machineName.getGlobalBounds().width, 0.36f * SCREEN_HEIGHT));
	//this->m_txt_ThomsonBrand.setLetterSpacing(2.0f); <-- SFML 2.5

	// Date
	this->m_txt_date.setFont(this->m_data->assetManager.GetFont("Thomson"));
	this->m_txt_date.setString("DATE:  " + getLocalDate());
	this->m_txt_date.setFillColor(COLOR_STONE_BLUE);
	this->m_txt_date.setCharacterSize(14);
	this->m_txt_date.setPosition(sf::Vector2f(xPos + 6.0f, 0.56f * SCREEN_HEIGHT));
	//this->m_txt_date.setLetterSpacing(2.0f); <-- SFML 2.5

	// Ram
	this->m_txt_ram = this->m_txt_date;
	this->m_txt_ram.setString("RAM:  512K");
	this->m_txt_ram.setOrigin(sf::Vector2f(m_txt_ram.getGlobalBounds().width + 6.0f, 0.0f));
	this->m_txt_ram.setPosition(sf::Vector2f(xPos + xOffset - 00.0f, 0.56f * SCREEN_HEIGHT));

	// Separator1
	this->m_shape_separator1.setFillColor(COLOR_STONE_BLUE);
	this->m_shape_separator1.setSize(sf::Vector2f(SCREEN_WIDTH - 0.05 * SCREEN_WIDTH, 2.0f));
	this->m_shape_separator1.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_shape_machineName.getGlobalBounds().width / 2), 0.6 * SCREEN_HEIGHT));

	// Optical pen Box1
	this->m_opticalPenBox1.setFillColor(COLOR_LIGHT_YELLOW);
	this->m_opticalPenBox1.setSize(sf::Vector2f(64.0f, 16.0f));
	this->m_opticalPenBox1.setOutlineColor(sf::Color(0, 122, 159, 255));
	this->m_opticalPenBox1.setOutlineThickness(2.0f);
	this->m_opticalPenBox1.setPosition(sf::Vector2f(xPos + 6.0f, 0.62f * SCREEN_HEIGHT));

	// Optical pen Box2
	this->m_opticalPenBox2 = this->m_opticalPenBox1;
	this->m_opticalPenBox2.setOrigin(sf::Vector2f(m_opticalPenBox2.getGlobalBounds().width + 6.0f, 0.0f));
	this->m_opticalPenBox2.setPosition(sf::Vector2f(SCREEN_WIDTH - 0.05f * SCREEN_WIDTH, 0.62 * SCREEN_HEIGHT));

	// Optical pen Box3
	this->m_opticalPenBox3 = this->m_opticalPenBox1;
	this->m_opticalPenBox1.setPosition(sf::Vector2f(xPos + 6.0f, 0.665f * SCREEN_HEIGHT));

	// Optical pen Box4
	this->m_opticalPenBox4 = this->m_opticalPenBox2;
	this->m_opticalPenBox4.setPosition(sf::Vector2f(SCREEN_WIDTH - 0.05f * SCREEN_WIDTH, 0.665 * SCREEN_HEIGHT));

	// Separator2
	this->m_shape_separator2 = this->m_shape_separator1;
	this->m_shape_separator2.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_shape_machineName.getGlobalBounds().width / 2), 0.72 * SCREEN_HEIGHT));

	// Optical pen Box5
	this->m_opticalPenBox5 = this->m_opticalPenBox3;
	this->m_opticalPenBox5.setPosition(sf::Vector2f(xPos + 6.0f, 0.74f * SCREEN_HEIGHT));

	// Optical pen Box6
	this->m_opticalPenBox6 = this->m_opticalPenBox5;
	this->m_opticalPenBox6.setPosition(sf::Vector2f(xPos + 6.0f, 0.785f * SCREEN_HEIGHT));

	// Optical pen Box7
	this->m_opticalPenBox7 = this->m_opticalPenBox2;
	this->m_opticalPenBox7.setPosition(sf::Vector2f(SCREEN_WIDTH - 0.05f * SCREEN_WIDTH, 0.785 * SCREEN_HEIGHT));

	// Optical pen Box8
	this->m_opticalPenBox8 = this->m_opticalPenBox6;
	this->m_opticalPenBox8.setPosition(sf::Vector2f(xPos + 6.0f, 0.83f * SCREEN_HEIGHT));

	// Separator3
	this->m_shape_separator3 = this->m_shape_separator2;
	this->m_shape_separator3.setPosition(sf::Vector2f((SCREEN_WIDTH / 2 - m_shape_machineName.getGlobalBounds().width / 2), 0.885 * SCREEN_HEIGHT));

	// String1
	this->m_txt_Str1 = this->m_txt_ram;
	this->m_txt_Str1.setFillColor(sf::Color::Black);
	this->m_txt_Str1.setString("1 BASIC 512 MICROSOFT 1.0");

	this->m_txt_Str1.setPosition(sf::Vector2f(xPos + 218.0f, 0.62 * SCREEN_HEIGHT));

	// String2
	this->m_txt_Str2 = this->m_txt_Str1;
	this->m_txt_Str1.setString("2 BASIC MICROSOFT 1.0");
	this->m_txt_Str1.setPosition(sf::Vector2f(xPos + 218.0f, 0.665 * SCREEN_HEIGHT));

	// String3
	this->m_txt_Str3 = this->m_txt_Str2;
	this->m_txt_Str3.setString(L"3 Réglage et préférences");
	this->m_txt_Str3.setPosition(sf::Vector2f(xPos + 218.0f, 0.74 * SCREEN_HEIGHT));

	// String4
	this->m_txt_Str4 = this->m_txt_Str3;
	this->m_txt_Str4.setString("4 Appel de programme");
	this->m_txt_Str4.setPosition(sf::Vector2f(xPos + 218.0f, 0.785 * SCREEN_HEIGHT));

	// String5
	this->m_txt_Str5 = this->m_txt_Str4;
	this->m_txt_Str5.setString("5 Exploitation de fichiers");
	this->m_txt_Str5.setPosition(sf::Vector2f(xPos + 218.0f, 0.83 * SCREEN_HEIGHT));

	// String6
	this->m_txt_Str6 = this->m_txt_Str1;
	this->m_txt_Str6.setOrigin(sf::Vector2f(0, 0));
	this->m_txt_Str6.setString("B");
	this->m_txt_Str6.setPosition(sf::Vector2f(SCREEN_WIDTH - 0.05 * SCREEN_WIDTH, 0.62 * SCREEN_HEIGHT));

	// String8
	this->m_txt_Str7 = this->m_txt_Str6;
	this->m_txt_Str7.setString("C");
	this->m_txt_Str7.setPosition(sf::Vector2f(SCREEN_WIDTH - 0.05 * SCREEN_WIDTH, 0.665 * SCREEN_HEIGHT));

	// String8
	this->m_txt_Str8 = this->m_txt_Str6;
	this->m_txt_Str8.setString("E");
	this->m_txt_Str8.setPosition(sf::Vector2f(SCREEN_WIDTH - 0.05 * SCREEN_WIDTH, 0.785 * SCREEN_HEIGHT));
}

void SplashScreen::Draw()
{
	this->m_data->window.draw(this->m_shape_machineName);
	this->m_data->window.draw(this->m_txt_machineName);
	this->m_data->window.draw(this->m_txt_ThomsonBrand);
	this->m_data->window.draw(this->m_txt_version);
	this->m_data->window.draw(this->m_txt_date);
	this->m_data->window.draw(this->m_txt_ram);
	this->m_data->window.draw(this->m_shape_separator1);
	this->m_data->window.draw(this->m_opticalPenBox1);
	this->m_data->window.draw(this->m_opticalPenBox2);
	this->m_data->window.draw(this->m_opticalPenBox3);
	this->m_data->window.draw(this->m_opticalPenBox4);
	this->m_data->window.draw(this->m_shape_separator2);
	this->m_data->window.draw(this->m_opticalPenBox5);
	this->m_data->window.draw(this->m_opticalPenBox6);
	this->m_data->window.draw(this->m_opticalPenBox7);
	this->m_data->window.draw(this->m_opticalPenBox8);
	this->m_data->window.draw(this->m_shape_separator3);
	this->m_data->window.draw(this->m_txt_Str1);
	this->m_data->window.draw(this->m_txt_Str2);
	this->m_data->window.draw(this->m_txt_Str3);
	this->m_data->window.draw(this->m_txt_Str4);
	this->m_data->window.draw(this->m_txt_Str5);
	this->m_data->window.draw(this->m_txt_Str6);
	this->m_data->window.draw(this->m_txt_Str7);
	this->m_data->window.draw(this->m_txt_Str8);
}

std::string SplashScreen::getLocalDate()
{
	time_t t = time(0);
	struct tm* timeStruct = localtime(&t);

	int numberOfZero{ 0 };

	std::string tmp_strDay = std::to_string(timeStruct->tm_mday);
	numberOfZero = 2 - tmp_strDay.length();
	std::string strDay = std::string(numberOfZero, '0').append(tmp_strDay);

	std::string tmp_strMonth = std::to_string(timeStruct->tm_mon + 1);
	numberOfZero = 2 - tmp_strMonth.length();
	std::string strMonth = std::string(numberOfZero, '0').append(tmp_strMonth);

	std::string tmp_strYear = std::to_string(timeStruct->tm_year - 100);
	numberOfZero = 2 - tmp_strYear.length();
	std::string strYear = std::string(numberOfZero, '0').append(tmp_strYear);

	return  strDay + "-" + strMonth + "-" + strYear;
}