#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "Component.h"


namespace coconut {
	class Animation;
	class Image;
	class GameObject;

	class Sprite : public Component {
	public:
		Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object);
		~Sprite();
		void Load(const std::filesystem::path& spriteInfoFile, GameObject* object);
		void Update(double dt) override;
		void Draw(glm::mat3 displayMatrix);
		void PlayAnimation(int anim);
		int GetCurrentAnim();
		bool IsAnimationDone();
		glm::ivec2 GetHotSpot(int index);
		glm::ivec2 GetFrameSize() const;
	private:
		glm::ivec2 GetFrameTexel(int frameNum) const;
		Image* ImagePtr;
		int currAnim;
		glm::ivec2 frameSize;
		std::vector<glm::ivec2> frameTexel;
		std::vector<Animation*> animations;
		std::vector<glm::ivec2> hotSpotList;

		const char* filepath;
	};

}