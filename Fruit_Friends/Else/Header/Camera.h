#pragma once
#include "Rect.h"
#include "Component.h"

namespace math {
	class TransformMatrix;
}

namespace CS230 {
	class Camera : public Component {
	public:
		Camera(math::rect2 movableRange);
		void SetPosition(math::vec2 newPosition);
		const math::vec2& GetPosition() const;
		void SetExtent(math::irect2 newExtent);
		void Update(const math::vec2& followObjPos);
		math::TransformMatrix GetMatrix();
	private:
		math::irect2 extent;
		math::ivec2 position;
		math::rect2 movableRange;
	};
}