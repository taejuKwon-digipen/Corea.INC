// Geonhwi Sim

#include "..\Engine\Engine.h"
#include "..\Engine\MatrixOperator.h"
#include "..\Engine\Sprite.h"
#include "Button.h"

Button::Button() {}

void Button::Add(glm::ivec2 pos, const char* begin, const char* end, bool butBool)
{
    buttonVec.push_back(Buttons{ pos, Engine::GetTextureManager().Load(begin),
    Engine::GetTextureManager().Load(end), butBool });
}

void Button::Draw(int numb)
{
    Buttons& b = buttonVec[numb];
    double x = Engine::GetInput().get_mouse_x();
    double y = Engine::GetInput().get_mouse_y();
    b.startButton->Draw(coconut::math::TranslateMatrix(b.buttonLocation));
    if (x >= (b.buttonLocation.x + Size().x / 2) - Size().x / 2 && x <= (b.buttonLocation.x + Size().x / 2) + Size().x / 2 &&
        y >= (b.buttonLocation.y + Size().y / 2) - Size().y / 2 && y <= (b.buttonLocation.y + Size().y / 2) + Size().y / 2)
    {
        buttonVec[numb].endButton->Draw(coconut::math::TranslateMatrix(b.buttonLocation));
        if (Engine::GetInput().IsMouseReleased(InputMouse::MouseButtons::Left) == true)
        {
            b.mouseIsOver = true;
        }
    }
}

glm::ivec2 Button::Size()
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
    //const double mouseX = Window::mouseX;
    //const double mouseY = Window::mouseY;

    ///*const bool mouseXon = (posX) < mouseX && (posX) > mouseX;
    //const bool mouseYon = (posY) < mouseY && (posY) > mouseY;*/

    //mouseIsOver = mouseXon && mouseYon;

    //const bool clickedIt = mouseIsOver && mouseWasPressed && !Window::mouseIsPressed;
    //mouseWasPressed = Window::MouseIsPressed;

    //return clickedIt;

    return true;
}