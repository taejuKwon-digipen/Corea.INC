#include "../Header/ShowCollision.h"

ShowCollision::ShowCollision(InputKey::Keyboard keyToUse) : enabled(false), showCollisionKey(keyToUse) {}

void ShowCollision::Update(double) {
	if (showCollisionKey.IsKeyReleased() == true) {
		enabled = !enabled;
	}
}

bool ShowCollision::IsEnabled() {
	return enabled;
}