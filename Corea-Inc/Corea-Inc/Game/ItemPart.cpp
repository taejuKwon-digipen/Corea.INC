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

Item_First::Item_First(Hero* hero, int stagenum)  : hero(hero), stagenum(stagenum), escape(InputKey::KeyboardButtons::Escape), next_description(InputKey::KeyboardButtons::Enter) {
    stagenum = 1;
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

    potionVec.push_back(new Potion({ 350, 400 }, 0, "assets/ItemDepartment/potion1.png", "assets/ItemDepartment/potion1_pick.png"));
    potionVec.push_back(new Potion({ 500, 400 }, 1, "assets/ItemDepartment/potion2.png", "assets/ItemDepartment/potion2_pick.png"));
    potionVec.push_back(new Potion({ 650, 400 }, 2, "assets/ItemDepartment/potion3.png", "assets/ItemDepartment/potion3_pick.png"));
    potionVec.push_back(new Potion({ 800, 400 }, 3, "assets/ItemDepartment/potion4.png", "assets/ItemDepartment/potion4_pick.png"));
    potionVec.push_back(new Potion({ 950, 400 }, 4, "assets/ItemDepartment/potion5.png", "assets/ItemDepartment/potion5_pick.png"));
    potionVec.push_back(new Potion({ 0,0 }, 10, "assets/ItemDepartment/potion_mix.png", "assets/ItemDepartment/potion_mix.png"));
    potionVec.push_back(new Potion({ (double)Engine::GetWindow().GetSize().x - 100, (double)Engine::GetWindow().GetSize().y - 150 }, 10, "assets/ItemDepartment/guidebook.png", "assets/ItemDepartment/guidebook.png"));

    std::vector<const char*> beaker3;
    std::vector<const char*> beaker3_ch;

    std::vector<const char*> beaker5;
    std::vector<const char*> beaker5_ch;

    std::vector<const char*> full;
    std::vector<const char*> full_ch;

    std::vector<const char*> clear;
    std::vector<const char*> clear_ch;

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

    full.push_back("assets/ItemDepartment/beaker_orange.png");
    full_ch.push_back("assets/ItemDepartment/beaker_orange_p.png");

    clear.push_back("assets/ItemDepartment/beaker_pour.png");
    clear_ch.push_back("assets/ItemDepartment/beaker_pour_p.png");


    coconut::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));
    HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFFFFFFFF, true);
    PowerTexture = font.DrawTextToTexture("POWER: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
    DefenceTexture = font.DrawTextToTexture("DEFENCE: " + std::to_string(hero->getStat(Hero::herostat::defence)), 0xFFFFFFFF, true);
    LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
    IntelTexture = font.DrawTextToTexture("INTELIGENCE: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);


    //beaker A
    beakerVec.push_back(new Beaker({ 200, 300 }, 3, beaker3, beaker3_ch));
    //beaker B
    beakerVec.push_back(new Beaker({ 500, 300 }, 5, beaker5, beaker5_ch));
    //potion
    beakerVec.push_back(new Beaker({ 800, 300 }, 10, full, full_ch));
    //clear
    beakerVec.push_back(new Beaker({ 1100, 300 }, 0, clear, clear_ch));

    for (auto a : potionVec)
    {
        AddGSComponent(a);
    }

    for (auto a : beakerVec) {
        AddGSComponent(a);
    }

    description1 = Engine::GetTextureManager().Load("assets/ItemDepartment/item_instruction.png");
    description2 = Engine::GetTextureManager().Load("assets/ItemDepartment/item_instruction2.png");
    description3 = Engine::GetTextureManager().Load("assets/ItemDepartment/item_instruction3.png");
    guidebook_open = Engine::GetTextureManager().Load("assets/ItemDepartment/guidebook_open.png");

    answer = { (Hero::herostat)0, (Hero::herostat)2 };

    sound.water_drop();
    sound.water_mix();
}

void Item_First::ShowStats() {
    Hero::herostat stats = (Hero::herostat)0;
    std::string statsString;
    
    statsTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 500, 700 }));

    coconut::SpriteFont& font = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1));
    switch ((int)stats) {
    case 0:
        HPTexture = font.DrawTextToTexture("HP: " + std::to_string(hero->getStat(Hero::herostat::hp)), 0xFF99ccFF, true);
        break;
    case 1:
        PowerTexture = font.DrawTextToTexture("POWER: " + std::to_string(hero->getStat(Hero::herostat::attack)), 0xFFFFFFFF, true);
        break;
    case 2:
        DefenceTexture = font.DrawTextToTexture("DEFENCE: " + std::to_string(hero->getStat(Hero::herostat::defence)), 0xFFFFFFFF, true);
        break;
    case 3:
        LuckTexture = font.DrawTextToTexture("LUCK: " + std::to_string(hero->getStat(Hero::herostat::luck)), 0xFFFFFFFF, true);
        break;
    case 4:
        IntelTexture = font.DrawTextToTexture("INTELIGENCE: " + std::to_string(hero->getStat(Hero::herostat::intelligence)), 0xFFFFFFFF, true);
        break;
    }
    
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
        if (potionVec[5]->didClicked() == true) {

            sound.WATER_DROP.play();
            if (GetInput() == GetAnswer()) {
                iscleared = true;

                Engine::GetLogger().LogEvent(Part::Item,"1 clear!");

                isdone = true;
                part1 = true;
            }

            if (GetInput() != GetAnswer()) {
                iscleared = false;
                Engine::GetLogger().LogEvent(Part::Item, "1 not clear!");
                isdone = false;
                input.clear();
            }

            part1 = true;
        }
    }
    
    if (part1 == true) {
        if (beakerVec[1]->getRemain() == 4) {
            Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::MainGame));
            ClearGSComponent();
            potionVec.clear();
            beakerVec.clear();
            Load();
        }

        if (beakerVec[2]->IsChoiced() == true) {
            if (beakerVec[0]->IsChoiced() == true) {
                sound.WATER_POUR.play();
                beakerVec[0]->Into(beakerVec[2]);

                Engine::GetLogger().LogVerbose(Part::Item, "beaker3 :" + std::to_string(beakerVec[0]->getRemain()));
                Engine::GetLogger().LogVerbose(Part::Item, "beaker5 :" + std::to_string(beakerVec[1]->getRemain()));
            }

            if (beakerVec[1]->IsChoiced() == true) {
                beakerVec[1]->Into(beakerVec[2]);

                Engine::GetLogger().LogVerbose(Part::Item, "beaker3 :" + std::to_string(beakerVec[0]->getRemain()));
                Engine::GetLogger().LogVerbose(Part::Item, "beaker5 :" + std::to_string(beakerVec[1]->getRemain()));
            }

            if (beakerVec[2]->IsChoiced() == true) {
            }

            if (beakerVec[3]->IsChoiced() == true) {
            }
        }

        // isclicked3
        if (beakerVec[0]->IsChoiced() == true) {

            if (beakerVec[0]->IsChoiced() == true) {
            }

            if (beakerVec[1]->IsChoiced() == true && litter5 == false) {
                sound.WATER_POUR.play();
                beakerVec[1]->Into(beakerVec[0]);
                beakerVec[0]->updateRemain(beakerVec[1]->getLeft());

                Engine::GetLogger().LogVerbose(Part::Item, "beaker3 :" + std::to_string(beakerVec[0]->getRemain()));
                Engine::GetLogger().LogVerbose(Part::Item, "beaker5 :" + std::to_string(beakerVec[1]->getRemain()));
                litter3 = false;
            }

            if (beakerVec[2]->IsChoiced() == true) {
            }

            if (beakerVec[3]->IsChoiced() == true) {
            }
        }
        // isclicked5
        if (beakerVec[1]->IsChoiced() == true) {
            litter5 = true;

            if (beakerVec[0]->IsChoiced() == true && litter3 == false) {
                sound.WATER_POUR.play();
                beakerVec[0]->Into(beakerVec[1]);
                beakerVec[1]->updateRemain(beakerVec[0]->getLeft());

                Engine::GetLogger().LogVerbose(Part::Item, "beaker3 :" + std::to_string(beakerVec[0]->getRemain()));
                Engine::GetLogger().LogVerbose(Part::Item, "beaker5 :" + std::to_string(beakerVec[1]->getRemain()));
                litter5 = false;
            }

            if (beakerVec[1]->IsChoiced() == true) {
            }

            if (beakerVec[2]->IsChoiced() == true) {
            }

            if (beakerVec[3]->IsChoiced() == true) {
            }
        }
        // isclear
        if (beakerVec[3]->IsChoiced() == true) {
            if (beakerVec[0]->IsChoiced() == true) {
                beakerVec[0]->Into(beakerVec[3]);
                Engine::GetLogger().LogEvent(Part::Item, std::to_string(beakerVec[0]->getRemain()));
            }

            if (beakerVec[1]->IsChoiced() == true) {
                beakerVec[1]->Into(beakerVec[3]);
                Engine::GetLogger().LogEvent(Part::Item, std::to_string(beakerVec[1]->getRemain()));
            }

            if (beakerVec[2]->IsChoiced() == true) {
            }

            if (beakerVec[3]->IsChoiced() == true) {
            }
        }
    }
}

void Item_First::Draw() {
    GetGSComponent<Background>()->Draw();

    HPTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 10, Engine::GetWindow().GetSize().y - 100}));
    PowerTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 10, Engine::GetWindow().GetSize().y - 200 }));
    DefenceTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 10, Engine::GetWindow().GetSize().y - 300 }));
    LuckTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 10, Engine::GetWindow().GetSize().y - 400 }));
    IntelTexture.Draw(coconut::math::TranslateMatrix(glm::ivec2{ 10, Engine::GetWindow().GetSize().y - 500 }));

    coconut::math::TransformMatrix displayMatrix;

    if (part1 == true) {
        for (auto a : beakerVec) {
            a->Draw();
        }
    }
    else {
        for (auto a : potionVec)
        {
            a->Draw();
        }

        if (potionVec[6]->IsChoiced() == true) {
            guidebook_open->Draw(coconut::math::TranslateMatrix(glm::ivec2(0, 0)));
        }

        if (descriptionno == 0) {
            description1->Draw(coconut::math::TranslateMatrix(glm::ivec2{ Engine::GetWindow().GetSize().x/2 - description1->GetSize().x/2, Engine::GetWindow().GetSize().y/2 - description1->GetSize().y/2 }));
        }
        else if (descriptionno == 1) {
            description2->Draw(coconut::math::TranslateMatrix(glm::ivec2{ Engine::GetWindow().GetSize().x / 2 - description2->GetSize().x / 2, Engine::GetWindow().GetSize().y / 2 - description2->GetSize().y / 2 }));
        }
        else if (descriptionno == 2) {
            description3->Draw(coconut::math::TranslateMatrix(glm::ivec2{ Engine::GetWindow().GetSize().x / 2 - description3->GetSize().x / 2, Engine::GetWindow().GetSize().y / 2 - description3->GetSize().y / 2 }));
        }
    }
}

std::vector<Hero::herostat> Item_First::GetInput() {
    for (int i = 0; i < 5; i ++) {
        if (potionVec[i]->IsChoiced() == true) {
            input.push_back(potionVec[i]->GetStat());
        }
    }

    return input;
}

std::vector<Hero::herostat> Item_First::GetAnswer() {
	return answer;
}

bool Item_First::isCleared() {
	return iscleared;
}

bool Item_First::isDone() {
    return isdone;
}

void Item_First::Unload() {
    ClearGSComponent();
	answer.clear();
}

std::string Item_First::GetName() {
    return "Item_First";
}