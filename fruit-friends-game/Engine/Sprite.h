#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "Vec2.h"
#include "Component.h"

namespace math {
	class TransformMatrix;
}

class Texture;
class GameObject;
class Animation;

class Sprite : public Component {
public:
	Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
	~Sprite();
	void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
	void Update(double dt) override;
	void Draw(math::TransformMatrix displayMatrix);
	void PlayAnimation(int anim);
	int GetCurrentAnim();
	bool IsAnimationDone();
	math::ivec2 GetHotSpot(int index);
	math::ivec2 GetFrameSize() const;

private:
	math::ivec2 GetFrameTexel(int frameNum) const;

	Texture *texturePtr;
	int currAnim;
	math::ivec2 frameSize;
	std::vector<math::ivec2> frameTexel;
	std::vector<math::ivec2> hotSpotList;
	std::vector<Animation*> animations;
};