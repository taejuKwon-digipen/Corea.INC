#pragma once
#include "Input.h"
#include "Component.h"

class ShowCollision : public Component {
public:
    ShowCollision(InputKey::Keyboard keyToUse);
    void Update(double dt) override;
    bool IsEnabled();
private:
    bool enabled;
    InputKey showCollisionKey;
};