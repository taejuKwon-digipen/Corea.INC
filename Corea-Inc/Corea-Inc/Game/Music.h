#pragma once
#include "SFML/Audio.hpp"

class Music {
public:
	void mainmenu_bgm();
	sf::Music MAINMENU_BGM;

	sf::SoundBuffer B_page_turn;
	void page_turn();
	sf::Sound PAGE_TURN;

	sf::SoundBuffer B_stamp;
	void stamp();
	sf::Sound STAMP;

	sf::SoundBuffer B_portal;
	void portal();
	sf::Sound PORTAL;

	sf::SoundBuffer B_water_drop;
	void water_drop();
	sf::Sound WATER_DROP;

	sf::SoundBuffer B_water_mix;
	void water_mix();
	sf::Sound WATER_MIX;

	sf::SoundBuffer B_typing;
	void typing();
	sf::Sound TYPING;

	void walking();
	sf::Music WALKING;

	sf::SoundBuffer B_field_button;
	void field_button();
	sf::Sound FIELD_BUTTON;

	sf::SoundBuffer B_glass;
	void glass();
	sf::Sound GLASS;

	sf::SoundBuffer B_water_pour;
	void water_pour();
	sf::Sound WATER_POUR;
};