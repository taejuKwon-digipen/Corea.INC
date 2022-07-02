#include "../Header/Engine.h"
#include "../Header/Camera.h"

CS230::Camera::Camera(math::rect2 movableRange) : movableRange(movableRange), position({ 0,0 }) {}

void CS230::Camera::SetPosition(math::vec2 newPosition) {
	position = newPosition;
}

const math::vec2& CS230::Camera::GetPosition() const {
	return position;
}

void CS230::Camera::SetExtent(math::irect2 newExtent) {
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos) {
	if (followObjPos.x > movableRange.Right() + position.x) {
		 position.x = followObjPos.x - movableRange.Right();
	}
	if (followObjPos.x - position.x < movableRange.Left()) {
		position.x = followObjPos.x - movableRange.Left();
	}

	if (position.x < extent.Left()) {
		position.x = extent.Left();
	}
	if (position.x > extent.Right()) {
		position.x = extent.Right();
	}
	if (position.y < extent.Bottom()) {
		position.y = extent.Bottom();
	}
	if (position.y > extent.Top()) {
		position.y = extent.Top();
	}
}

math::TransformMatrix CS230::Camera::GetMatrix() {
	return math::TransformMatrix(-position);
}