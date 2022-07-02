//Juhong Mo

#include "ItemPart.h"
#include <algorithm>
#include <string>
#include <iostream>

#include "Background.h"
#include "Screens.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Component.h"
#include "Fonts.h"

Item_First::Item_First(Hero* hero)  : hero(hero), escape(InputKey::Keyboard::Escape), next_description(InputKey::Keyboard::Enter) {
    descriptionno = 0;
    part1 = false;
    litter3 = false;
    litter5 = false;
}

void Item_First::Load() {
    AddGSComponent(new Background());
    GetGSComponent<Background>()->Add("assets/ItemDepartment/item_bg.png");

    potionVec.clear();
    beakerVec.clear();

    iscleared = false;
    isdone = false;
    part1 = false;

    //switch (level)
    //{
    //default:
    //    potionVec.push_back(new Potion({ 350, 400 }, 0, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    //    potionVec.push_back(new Potion({ 500, 400 }, 1, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    //    potionVec.push_back(new Potion({ 650, 400 }, 2, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    //    potionVec.push_back(new Potion({ 800, 400 }, 3, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    //    potionVec.push_back(new Potion({ 950, 400 }, 4, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    //    break;
    //case 1:
    //    potionVec.push_back(new Potion({ 350, 400 }, 0, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    //    potionVec.push_back(new Potion({ 500, 400 }, 1, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    //    potionVec.push_back(new Potion({ 650, 400 }, 2, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    //    potionVec.push_back(new Potion({ 800, 400 }, 3, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    //    potionVec.push_back(new Potion({ 950, 400 }, 4, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    //    break;
    //case 2:
    //    potionVec.push_back(new Potion({ 350, 400 }, 0, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    //    potionVec.push_back(new Potion({ 500, 400 }, 1, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    //    potionVec.push_back(new Potion({ 650, 400 }, 2, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    //    potionVec.push_back(new Potion({ 800, 400 }, 3, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    //    potionVec.push_back(new Potion({ 950, 400 }, 4, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    //    potionVec.push_back(new Potion({ 350, 600 }, 5, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    //    potionVec.push_back(new Potion({ 500, 600 }, 6, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    //    potionVec.push_back(new Potion({ 650, 600 }, 7, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    //    potionVec.push_back(new Potion({ 800, 600 }, 8, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    //    potionVec.push_back(new Potion({ 950, 600 }, 9, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    //    break;
    //case 3:
    potionVec.push_back(new Potion({ 0,0 }, 20, "assets/ItemDepartment/potion_mix.png", "assets/ItemDepartment/potion_mix.png"));
    potionVec.push_back(new Potion({ (double)Engine::GetWindow().GetSize().x - 100, (double)Engine::GetWindow().GetSize().y - 150 }, 20,
        "assets/ItemDepartment/guidebook.png", "assets/ItemDepartment/guidebook.png"));
    potionVec.push_back(new Potion({ 350, 400 }, 2, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    potionVec.push_back(new Potion({ 500, 400 }, 3, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    potionVec.push_back(new Potion({ 650, 400 }, 4, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    potionVec.push_back(new Potion({ 800, 400 }, 5, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    potionVec.push_back(new Potion({ 950, 400 }, 6, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    potionVec.push_back(new Potion({ 350, 600 }, 7, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    potionVec.push_back(new Potion({ 500, 600 }, 8, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    potionVec.push_back(new Potion({ 650, 600 }, 9, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    potionVec.push_back(new Potion({ 800, 600 }, 10, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    potionVec.push_back(new Potion({ 950, 600 }, 11, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    potionVec.push_back(new Potion({ 350, 200 }, 12, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    potionVec.push_back(new Potion({ 500, 200 }, 13, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    potionVec.push_back(new Potion({ 650, 200 }, 14, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    potionVec.push_back(new Potion({ 800, 200 }, 15, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    potionVec.push_back(new Potion({ 950, 200 }, 16, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    //    break;
    //}



    std::vector<std::filesystem::path> beaker3;
    std::vector<std::filesystem::path> beaker3_ch;

    std::vector<std::filesystem::path> beaker5;
    std::vector<std::filesystem::path> beaker5_ch;

    std::vector<std::filesystem::path> beaker4;
    std::vector<std::filesystem::path> beaker4_ch;

    std::vector<std::filesystem::path> beaker7;
    std::vector<std::filesystem::path> beaker7_ch;

    std::vector<std::filesystem::path> beakerA;
    std::vector<std::filesystem::path> beakerA_ch;

    std::vector<std::filesystem::path> beakerB;
    std::vector<std::filesystem::path> beakerB_ch;

    std::vector<std::filesystem::path> full;
    std::vector<std::filesystem::path> full_ch;

    std::vector<std::filesystem::path> clear;
    std::vector<std::filesystem::path> clear_ch;

    beaker3.push_back("assets/ItemDepartment/beaker3.png");
    beaker3.push_back("assets/ItemDepartment/beaker3_1.png");
    beaker3.push_back("assets/ItemDepartment/beaker3_2.png");
    beaker3.push_back("assets/ItemDepartment/beaker3_full.png");

    beaker3_ch.push_back("assets/ItemDepartment/beaker3_p.png");
    beaker3_ch.push_back("assets/ItemDepartment/beaker3_1_p.png");
    beaker3_ch.push_back("assets/ItemDepartment/beaker3_2_p.png");
    beaker3_ch.push_back("assets/ItemDepartment/beaker3_full_p.png");

    beaker5.push_back("assets/ItemDepartment/beaker5.png");
    beaker5.push_back("assets/ItemDepartment/beaker5_1.png");
    beaker5.push_back("assets/ItemDepartment/beaker5_2.png");
    beaker5.push_back("assets/ItemDepartment/beaker5_3.png");
    beaker5.push_back("assets/ItemDepartment/beaker5_4.png");
    beaker5.push_back("assets/ItemDepartment/beaker5_full.png");

    beaker5_ch.push_back("assets/ItemDepartment/beaker5_p.png");
    beaker5_ch.push_back("assets/ItemDepartment/beaker5_1_p.png");
    beaker5_ch.push_back("assets/ItemDepartment/beaker5_2_p.png");
    beaker5_ch.push_back("assets/ItemDepartment/beaker5_3_p.png");
    beaker5_ch.push_back("assets/ItemDepartment/beaker5_4_p.png");
    beaker5_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");


    beaker4.push_back("assets/ItemDepartment/beaker3.png");
    beaker4.push_back("assets/ItemDepartment/beaker3_1.png");
    beaker4.push_back("assets/ItemDepartment/beaker3_2.png");
    beaker4.push_back("assets/ItemDepartment/beaker3_full.png");
    beaker4.push_back("assets/ItemDepartment/beaker3_full.png");

    beaker4_ch.push_back("assets/ItemDepartment/beaker3_p.png");
    beaker4_ch.push_back("assets/ItemDepartment/beaker3_1_p.png");
    beaker4_ch.push_back("assets/ItemDepartment/beaker3_2_p.png");
    beaker4_ch.push_back("assets/ItemDepartment/beaker3_full_p.png");
    beaker4_ch.push_back("assets/ItemDepartment/beaker3_full_p.png");

    beaker7.push_back("assets/ItemDepartment/beaker5.png");
    beaker7.push_back("assets/ItemDepartment/beaker5_1.png");
    beaker7.push_back("assets/ItemDepartment/beaker5_2.png");
    beaker7.push_back("assets/ItemDepartment/beaker5_3.png");
    beaker7.push_back("assets/ItemDepartment/beaker5_4.png");
    beaker7.push_back("assets/ItemDepartment/beaker5_full.png");
    beaker7.push_back("assets/ItemDepartment/beaker5_full.png");
    beaker7.push_back("assets/ItemDepartment/beaker5_full.png");

    beaker7_ch.push_back("assets/ItemDepartment/beaker5_p.png");
    beaker7_ch.push_back("assets/ItemDepartment/beaker5_1_p.png");
    beaker7_ch.push_back("assets/ItemDepartment/beaker5_2_p.png");
    beaker7_ch.push_back("assets/ItemDepartment/beaker5_3_p.png");
    beaker7_ch.push_back("assets/ItemDepartment/beaker5_4_p.png");
    beaker7_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");
    beaker7_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");
    beaker7_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");


    beakerA.push_back("assets/ItemDepartment/beaker3.png");

    beakerA_ch.push_back("assets/ItemDepartment/beaker3_p.png");

    beakerB.push_back("assets/ItemDepartment/beaker5.png");

    beakerB_ch.push_back("assets/ItemDepartment/beaker5_p.png");


    full.push_back("assets/ItemDepartment/beaker_orange.png");
    full_ch.push_back("assets/ItemDepartment/beaker_orange_p.png");

    clear.push_back("assets/ItemDepartment/beaker_pour.png");
    clear_ch.push_back("assets/ItemDepartment/beaker_pour_p.png");

    /*SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));
    HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFFFFFFFF, true);
    PowerTexture = font.DrawTextToTexture("POWER: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
    DefenceTexture = font.DrawTextToTexture("DEFENCE: " + std::to_string(hero->getStat(Hero::herostat::defence)), 0xFFFFFFFF, true);
    LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
    IntelTexture = font.DrawTextToTexture("INTELIGENCE: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);*/


    //potion
    beakerVec.push_back(new Beaker({ 800, 300 }, 10, full, full_ch));
    //clear
    beakerVec.push_back(new Beaker({ 1100, 300 }, 0, clear, clear_ch));
    //beaker A - 1
    beakerVec.push_back(new Beaker({ 200, 300 }, 3, beaker3, beaker3_ch));
    //beaker B - 1
    beakerVec.push_back(new Beaker({ 500, 300 }, 5, beaker5, beaker5_ch));
    //beaker A - 2
    beakerVec.push_back(new Beaker({ 200, 300 }, 4, beaker4, beaker4_ch));
    //beaker B - 2
    beakerVec.push_back(new Beaker({ 500, 300 }, 7, beaker7, beaker7_ch));
    //beakerA - 3
    beakerVec.push_back(new Beaker({ 200, 300 }, 1, beakerA, beakerA_ch));
    //beakerB - 3
    beakerVec.push_back(new Beaker({ 500, 300 }, 1, beakerB, beakerB_ch));

    for (auto a : potionVec)
    {
        AddGSComponent(a);
    }

    for (auto a : beakerVec) {
        AddGSComponent(a);
    }

    //beakerChange();

    herostat = Engine::GetTextureManager().Load("assets/ItemDepartment/hero_stat.png");
    description1 = Engine::GetTextureManager().Load("assets/ItemDepartment/item_instruction.png");
    description2 = Engine::GetTextureManager().Load("assets/ItemDepartment/item_instruction2.png");
    description3 = Engine::GetTextureManager().Load("assets/ItemDepartment/item_instruction3.png");
    guidebook_open = Engine::GetTextureManager().Load("assets/ItemDepartment/guidebook_open.png");

    //answer = { (Hero::herostat)0, (Hero::herostat)2 };

    sound.water_drop();
    sound.water_mix();
}

void Item_First::ShowStats() {
    Hero::herostat stats = (Hero::herostat)0;
    std::string statsString;
    
    statsTexture.Draw(math::TranslateMatrix(math::ivec2{ 500, 700 }));

    SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));
    //switch ((int)stats) {
    //case 0:
    //    HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFF99ccFF, true);
    //    break;
    //case 1:
    //    PowerTexture = font.DrawTextToTexture("POWR: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
    //    break;
    //case 2:
    //    DefenceTexture = font.DrawTextToTexture("DEFENCE: " + std::to_string(hero->getStat(Hero::herostat::defence)), 0xFFFFFFFF, true);
    //    break;
    //case 3:
    //    LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
    //    break;
    //case 4:
    //    IntelTexture = font.DrawTextToTexture("INTELIGENCE: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);
    //    break;
    //}
    
    statsTexture = Engine::GetSpriteFont(2).DrawTextToTexture(statsString, 0xFFFFFFFF, true);
}

void Item_First::Update(double dt) {
    UpdateGSComponents(dt);

    if (next_description.IsKeyReleased() == true) {
        descriptionno++;
    }

    if (escape.IsKeyReleased() == true)
    {
        Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
    }

    if (part1 == false) {
        if (potionVec[0]->didClicked() == true) {

            sound.WATER_DROP.play();
            if (GetInput() == GetAnswer()) {
                iscleared = true;

                Engine::GetLogger().LogEvent("1 clear!");

                isdone = true;
            }

            else if (GetInput() != GetAnswer()) {
                iscleared = false;
                Engine::GetLogger().LogEvent("1 not clear!");
                isdone = false;
                input.clear();
            }

            part1 = true;
        }
    }
    
    if (part1 == true) {
        switch (level) {
        case 1:
            if (beakerVec[3]->getRemain() == 4 && level == 1) {
                isfinished = true;

                Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));

                //isfinished = false;
                ClearGSComponent();
                potionVec.clear();
                beakerVec.clear();
                Load();
            }

            if (beakerVec[0]->IsChoiced() == true) {
                if (beakerVec[2]->IsChoiced() == true) {
                    sound.WATER_POUR.play();
                    beakerVec[2]->Into(beakerVec[0]);

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[2]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[3]->getRemain()));
                }

                if (beakerVec[3]->IsChoiced() == true) {
                    beakerVec[3]->Into(beakerVec[0]);

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[2]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[3]->getRemain()));
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }

            // isclicked3
            if (beakerVec[2]->IsChoiced() == true) {

                if (beakerVec[2]->IsChoiced() == true) {
                }

                if (beakerVec[3]->IsChoiced() == true && litter5 == false) {
                    sound.WATER_POUR.play();
                    beakerVec[3]->Into(beakerVec[2]);
                    beakerVec[2]->updateRemain(beakerVec[3]->getLeft());

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[2]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[3]->getRemain()));
                    litter3 = false;
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }
            // isclicked5
            if (beakerVec[3]->IsChoiced() == true) {
                litter5 = true;

                if (beakerVec[2]->IsChoiced() == true && litter3 == false) {
                    sound.WATER_POUR.play();
                    beakerVec[2]->Into(beakerVec[3]);
                    beakerVec[3]->updateRemain(beakerVec[2]->getLeft());

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[2]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[3]->getRemain()));
                    litter5 = false;
                }

                if (beakerVec[3]->IsChoiced() == true) {
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }
            // isclear
            if (beakerVec[1]->IsChoiced() == true) {
                if (beakerVec[2]->IsChoiced() == true) {
                    beakerVec[2]->Into(beakerVec[1]);
                    Engine::GetLogger().LogEvent(std::to_string(beakerVec[2]->getRemain()));
                }

                if (beakerVec[3]->IsChoiced() == true) {
                    beakerVec[3]->Into(beakerVec[1]);
                    Engine::GetLogger().LogEvent(std::to_string(beakerVec[3]->getRemain()));
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }
            break;

        case 2:
            if (beakerVec[5]->getRemain() == 6 && level == 2) {
                isfinished = true;

                Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));

                //isfinished = false;
                ClearGSComponent();
                potionVec.clear();
                beakerVec.clear();
                Load();
            }

            if (beakerVec[0]->IsChoiced() == true) {
                if (beakerVec[4]->IsChoiced() == true) {
                    sound.WATER_POUR.play();
                    beakerVec[4]->Into(beakerVec[0]);

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[4]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[5]->getRemain()));
                }

                if (beakerVec[5]->IsChoiced() == true) {
                    beakerVec[5]->Into(beakerVec[0]);

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[4]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[5]->getRemain()));
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }

            // isclicked3
            if (beakerVec[4]->IsChoiced() == true) {

                if (beakerVec[4]->IsChoiced() == true) {
                }

                if (beakerVec[5]->IsChoiced() == true && litter5 == false) {
                    sound.WATER_POUR.play();
                    beakerVec[5]->Into(beakerVec[4]);
                    beakerVec[4]->updateRemain(beakerVec[5]->getLeft());

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[4]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[5]->getRemain()));
                    litter3 = false;
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }
            // isclicked5
            if (beakerVec[5]->IsChoiced() == true) {
                litter5 = true;

                if (beakerVec[4]->IsChoiced() == true && litter3 == false) {
                    sound.WATER_POUR.play();
                    beakerVec[4]->Into(beakerVec[5]);
                    beakerVec[5]->updateRemain(beakerVec[4]->getLeft());

                    Engine::GetLogger().LogVerbose("beaker3 :" + std::to_string(beakerVec[4]->getRemain()));
                    Engine::GetLogger().LogVerbose("beaker5 :" + std::to_string(beakerVec[5]->getRemain()));
                    litter5 = false;
                }

                if (beakerVec[5]->IsChoiced() == true) {
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }
            // isclear
            if (beakerVec[1]->IsChoiced() == true) {
                if (beakerVec[4]->IsChoiced() == true) {
                    beakerVec[4]->Into(beakerVec[1]);
                    Engine::GetLogger().LogEvent(std::to_string(beakerVec[4]->getRemain()));
                }

                if (beakerVec[5]->IsChoiced() == true) {
                    beakerVec[5]->Into(beakerVec[1]);
                    Engine::GetLogger().LogEvent(std::to_string(beakerVec[5]->getRemain()));
                }

                if (beakerVec[0]->IsChoiced() == true) {
                }

                if (beakerVec[1]->IsChoiced() == true) {
                }
            }
            break;
        }
    }
}

void Item_First::Draw() {
    GetGSComponent<Background>()->Draw();

    herostat->Draw(math::TranslateMatrix(math::ivec2(10, Engine::GetWindow().GetSize().y - 450)));

    //HPTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, Engine::GetWindow().GetSize().y - 100}), math::ivec2(120, 30));
    //PowerTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, Engine::GetWindow().GetSize().y - 200 }));
    //DefenceTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, Engine::GetWindow().GetSize().y - 300 }));
    //LuckTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, Engine::GetWindow().GetSize().y - 400 }));
    //IntelTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, Engine::GetWindow().GetSize().y - 500 }));

    //Engine::GetLogger().LogVerbose("H P | " + std::to_string(hero->getStat(Hero::herostat::hp)));
    //Engine::GetLogger().LogVerbose("POW | " + std::to_string(hero->getStat(Hero::herostat::attack)));
    //Engine::GetLogger().LogVerbose("LUK | " + std::to_string(hero->getStat(Hero::herostat::luck)));
    //Engine::GetLogger().LogVerbose("INT | " + std::to_string(hero->getStat(Hero::herostat::intelligence)));

    math::TransformMatrix displayMatrix;

    if (part1 == true) {
        switch (level) {
        case 1:
            for (int i = 0; i < 4; i++) {
                beakerVec[i]->Draw();
            }
            break;

        case 2:
            for (int i = 0; i < 2; i++) {
                beakerVec[i]->Draw();
            }
            for (int i = 4; i < 6; i++) {
                beakerVec[i]->Draw();
            }
            break;

        case 3:
            for (int i = 0; i < 2; i++) {
                beakerVec[i]->Draw();
            }
            for (int i = 6; i < 8; i++) {
                beakerVec[i]->Draw();
            }
        }
    }
    else {
        switch (level) {
        case 1:
            for (int i = 0; i < 7; i++) {
                potionVec[i]->Draw();
            }
            break;
        case 2:
            for (int i = 0; i < 12; i++) {
                potionVec[i]->Draw();
            }
            break;
        case 3:
            for (int i = 0; i < 17; i++) {
                potionVec[i]->Draw();
            }
        }
        /*for (auto a : potionVec)
        {
            a->Draw();
        }*/

        if (potionVec[1]->IsChoiced() == true) {
            guidebook_open->Draw(math::TranslateMatrix(math::ivec2(0, 0)));
        }

        if (descriptionno == 0) {
            description1->Draw(math::TranslateMatrix({ Engine::GetWindow().GetSize() / 2 - description1->GetSize() / 2 }));
        }
        else if (descriptionno == 1) {
            description2->Draw(math::TranslateMatrix({ Engine::GetWindow().GetSize() / 2 - description2->GetSize() / 2 }));
        }
        else if (descriptionno == 2) {
            description3->Draw(math::TranslateMatrix({ Engine::GetWindow().GetSize() / 2 - description3->GetSize() / 2 }));
        }
    }
}

std::vector<Hero::herostat> Item_First::GetInput() {
    //switch (level) {
    //case 1:
    //    for (int i = 2; i < 7; i++) {
    //        if (potionVec[i]->IsChoiced() == true) {
    //            input.push_back(potionVec[i]->GetStat());
    //        }
    //    }
    //    break;
    //case 2:
    //    for (int i = 2; i < 12; i++) {
    //        if (potionVec[i]->IsChoiced() == true) {
    //            input.push_back(potionVec[i]->GetStat());
    //        }
    //    }
    //    break;
    //case 3:
    //    for (int i = 2; i < 17; i++) {
    //        if (potionVec[i]->IsChoiced() == true) {
    //            input.push_back(potionVec[i]->GetStat());
    //        }
    //    }
    //    break;
    //}
    input.clear();

    for (int i = 2; i < potionVec.size() - 1; i++) {
        if (potionVec[i]->IsChoiced() == true) {
            input.push_back(potionVec[i]->GetStat());
        }
    }

    return input;
}

std::vector<Hero::herostat> Item_First::GetAnswer() {
    answer.clear();

    switch (level)
    {
    default:
        answer = {};
        break;
    case 1:
        answer.push_back(Hero::herostat::attack);
        answer.push_back(Hero::herostat::hp);
        break;
    case 2:
        answer.push_back(Hero::herostat::attack);
        answer.push_back(Hero::herostat::defence);
        answer.push_back(Hero::herostat::heal);
        answer.push_back(Hero::herostat::attspeed);
        break;
    case 3:
        answer.push_back(Hero::herostat::attack);
        answer.push_back(Hero::herostat::hp);
        answer.push_back(Hero::herostat::intelligence);
        answer.push_back(Hero::herostat::luck);
        answer.push_back(Hero::herostat::critical);
        answer.push_back(Hero::herostat::bossattack);
        answer.push_back(Hero::herostat::debuff);
        break;
    }

	return answer;
}

bool Item_First::isCleared() {
	return iscleared;
}

void Item_First::changeStatus() {
    isfinished = false;
}

bool Item_First::isFinished() {
    return isfinished;
}

void Item_First::Unload() {
    ClearGSComponent();
}

std::string Item_First::GetName() {
    return "Item_First";
}

void Item_First::getLevel(int level) {
    this->level = level;
}

void Item_First::clearVector() {
    input.clear();
}

//void Item_First::beakerChange() {
//    beakerVec.clear();
//
//    std::vector<std::filesystem::path> beakerA;
//    std::vector<std::filesystem::path> beakerA_ch;
//
//    std::vector<std::filesystem::path> beakerB;
//    std::vector<std::filesystem::path> beakerB_ch;
//
//    std::vector<std::filesystem::path> full;
//    std::vector<std::filesystem::path> full_ch;
//
//    std::vector<std::filesystem::path> clear;
//    std::vector<std::filesystem::path> clear_ch;
//
//    int beakerAsize, beakerBsize;
//
//    switch (level)
//    {
//    case 1:
//        beakerAsize = 3;
//        beakerBsize = 5;
//
//        beakerA.push_back("assets/ItemDepartment/beaker3.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_1.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_2.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_full.png");
//
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_1_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_2_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_full_p.png");
//
//        beakerB.push_back("assets/ItemDepartment/beaker5.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_1.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_2.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_3.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_4.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_full.png");
//
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_1_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_2_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_3_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_4_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");
//        break;
//
//    case 2:
//        beakerAsize = 4;
//        beakerBsize = 7;
//
//        beakerA.push_back("assets/ItemDepartment/beaker3.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_1.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_2.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_full.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_full.png");
//
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_1_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_2_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_full_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_full_p.png");
//
//        beakerB.push_back("assets/ItemDepartment/beaker5.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_1.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_2.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_3.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_4.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_full.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_full.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_full.png");
//
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_1_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_2_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_3_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_4_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");
//        break;
//
//    case 3:
//        beakerAsize = 3;
//        beakerBsize = 5;
//
//        beakerA.push_back("assets/ItemDepartment/beaker3.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_1.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_2.png");
//        beakerA.push_back("assets/ItemDepartment/beaker3_full.png");
//
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_1_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_2_p.png");
//        beakerA_ch.push_back("assets/ItemDepartment/beaker3_full_p.png");
//
//        beakerB.push_back("assets/ItemDepartment/beaker5.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_1.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_2.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_3.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_4.png");
//        beakerB.push_back("assets/ItemDepartment/beaker5_full.png");
//
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_1_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_2_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_3_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_4_p.png");
//        beakerB_ch.push_back("assets/ItemDepartment/beaker5_full_p.png");
//        break;
//
//    }
//
//    full.push_back("assets/ItemDepartment/beaker_orange.png");
//    full_ch.push_back("assets/ItemDepartment/beaker_orange_p.png");
//
//    clear.push_back("assets/ItemDepartment/beaker_pour.png");
//    clear_ch.push_back("assets/ItemDepartment/beaker_pour_p.png");
//
//    //potion
//    beakerVec.push_back(new Beaker({ 800, 300 }, 10, full, full_ch));
//    //clear
//    beakerVec.push_back(new Beaker({ 1100, 300 }, 0, clear, clear_ch));
//    //beaker A - 2
//    beakerVec.push_back(new Beaker({ 200, 300 }, 4, beakerA, beakerA_ch));
//    //beaker B - 2
//    beakerVec.push_back(new Beaker({ 500, 300 }, 7, beakerB, beakerB_ch));
//
//
//    for (auto a : beakerVec) {
//        AddGSComponent(a);
//    }
//}