#include "Music.h"
#include <iostream>

void Music::mainmenu_bgm() {
//#ifdef  _DEBUG
//	if (!MAINMENU_BGM.openFromFile("assets/main_menu_bgm.wav"))
//	{
//		std::cout << "No such file" << std::endl;
//	}
//#endif
	MAINMENU_BGM.openFromFile("assets/Sound/main_menu_bgm.wav");
	MAINMENU_BGM.setVolume(15);
}

void Music::page_turn() {
	B_page_turn.loadFromFile("assets/Sound/paper_turn.wav");
	PAGE_TURN.setBuffer(B_page_turn);
	PAGE_TURN.setVolume(400);
}

void Music::stamp() {
	B_stamp.loadFromFile("assets/Sound/stamp3.wav");
	STAMP.setBuffer(B_stamp);
	STAMP.setVolume(300);
}

void Music::portal() {
	B_portal.loadFromFile("assets/Sound/portal.wav");
	PORTAL.setBuffer(B_portal);
	PORTAL.setVolume(300);
}

void Music::water_drop() {
	B_water_drop.loadFromFile("assets/Sound/water_drop.wav");
	WATER_DROP.setBuffer(B_water_drop);
	WATER_DROP.setVolume(300);
}

void Music::water_mix() {
	B_water_mix.loadFromFile("assets/Sound/water_mix.wav");
	WATER_MIX.setBuffer(B_water_mix);
	WATER_MIX.setVolume(300);
}

void Music::typing() {
	B_typing.loadFromFile("assets/Sound/keyboard_typing.wav");
	TYPING.setBuffer(B_typing);
	TYPING.setVolume(300);
}

void Music::walking() {
	WALKING.openFromFile("assets/Sound/walking4.wav");
	WALKING.setVolume(400);
	WALKING.setLoop(true);
}

void Music::field_button() {
	B_field_button.loadFromFile("assets/Sound/stamp2.wav");
	FIELD_BUTTON.setBuffer(B_field_button);
	FIELD_BUTTON.setVolume(1000);
}

void Music::glass() {
	B_glass.loadFromFile("assets/Sound/glass.wav");
	GLASS.setBuffer(B_glass);
	GLASS.setVolume(300);
}

void Music::water_pour() {
	B_water_pour.loadFromFile("assets/Sound/water_pour1.wav");
	WATER_POUR.setBuffer(B_water_pour);
	WATER_POUR.setVolume(250);
}