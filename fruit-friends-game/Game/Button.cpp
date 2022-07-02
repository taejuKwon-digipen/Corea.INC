// Geonhwi Sim

#include "..\Engine\Engine.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine\Sprite.h"
#include "Button.h"

using namespace doodle;

Button::Button() {}

void Button::Add(math::ivec2 pos, const std::filesystem::path& begin, const std::filesystem::path& end, bool butBool)
{
    buttonVec.push_back(Buttons{ pos, Engine::GetTextureManager().Load(begin),
    Engine::GetTextureManager().Load(end), butBool });
}

void Button::Draw(int numb)
{
    Buttons& b = buttonVec[numb];
    double x = get_mouse_x();
    double y = get_mouse_y();
    b.startButton->Draw(math::TranslateMatrix(b.buttonLocation));
    if (x >= (b.buttonLocation.x + Size().x / 2) - Size().x / 2 && x <= (b.buttonLocation.x + Size().x / 2) + Size().x / 2 &&
        y >= (b.buttonLocation.y + Size().y / 2) - Size().y / 2 && y <= (b.buttonLocation.y + Size().y / 2) + Size().y / 2)
    {
        buttonVec[numb].endButton->Draw(math::TranslateMatrix(b.buttonLocation));
        if (Engine::GetInput().IsMouseReleased(InputMouse::Mouse::Left) == true)
        {
            b.mouseIsOver = true;
        }
    }
}

math::ivec2 Button::Size()
{
    return buttonVec[0].startButton->GetSize();
}

void Button::Unload()
{
    buttonVec.clear();
}

bool Button::GetBool(int numb)
{
    return buttonVec[numb].mouseIsOver;
}

bool Button::didClickButton()
{
    //const double mouseX = get_mouse_x();
    //const double mouseY = get_mouse_y();

    ///*const bool mouseXon = (posX) < mouseX && (posX) > mouseX;
    //const bool mouseYon = (posY) < mouseY && (posY) > mouseY;*/

    //mouseIsOver = mouseXon && mouseYon;

    //const bool clickedIt = mouseIsOver && mouseWasPressed && !doodle::MouseIsPressed;
    //mouseWasPressed = doodle::MouseIsPressed;

    //return clickedIt;

    return true;
}