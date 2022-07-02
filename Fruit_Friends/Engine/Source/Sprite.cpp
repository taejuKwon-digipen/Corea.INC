#include "../Header/Engine.h"			//Engine::GetLogger GetTextureManager
#include "../Header/Sprite.h"
#include "../Header/Animation.h"
//#include "../Header/Collision.h"
//#include "../Header/Texture.h"
#include "../Header/ComponentManager.h"
#include "../Header/GameObject.h"
#include "../Header/Image.h"
#include "../Header/Rect.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../Header/MatrixOperator.h"
#include "../Header/TexelImage.h"

#include <cstdlib>
#include <glm/gtx/transform.hpp>


using namespace coconut;
using namespace math;

Sprite::Sprite(const std::filesystem::path& spriteInfoFile, GameObject* object) {
	Load(spriteInfoFile, object);
}

Sprite::~Sprite() {
	for (Animation* anim : animations) {
		delete anim;
	}
	animations.clear();
}

void Sprite::Load(const std::filesystem::path& spriteInfoFile, GameObject* object) {
	animations.clear();
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	}

	std::string text;
	inFile >> text;
	const char* Imagetext = text.c_str();
	ImagePtr = Engine::GetImageManager().Load(Imagetext);
	frameSize = ImagePtr->GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames") {
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++) {
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else if (text == "Anim") {
			inFile >> text;
			animations.push_back(new Animation(text));
		}
		else if (text == "CollisionRect") {
			irect2 rect;
			inFile >> rect.point1.x >> rect.point1.y >> rect.point2.x >> rect.point2.y;
			if (object == nullptr) {
				Engine::GetLogger().LogError(Part::Entire, "Trying to add collision to a nullobject");
			}
			else {
				//object->AddGOComponent(new RectCollision(rect, object));
			}
		}
		else if (text == "CollisionCircle") {
			double radius;
			inFile >> radius;
			if (object == nullptr) {
				Engine::GetLogger().LogError(Part::Entire, "Trying to add collision to a nullobject");
			}
			else {
				//object->AddGOComponent(new CircleCollision(radius, object));
			}
		}
		else {
			Engine::GetLogger().LogError(Part::Entire, "Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
	if (animations.empty() == true) {
		animations.push_back(new Animation());
		PlayAnimation(0);
	}
}

glm::ivec2 Sprite::GetHotSpot(int index) {
	if (index >= hotSpotList.size()) {
		Engine::GetLogger().LogError(Part::Entire, "Sprite is missing hotspot index: " + std::to_string(index));
		return { 0,0 };
	}
	return hotSpotList[index];
}

void Sprite::PlayAnimation(int anim) {
	if (anim < 0 || anim >= animations.size()) {
		Engine::GetLogger().LogError(Part::Entire, "Animation " + std::to_string(anim) + " not found");
		currAnim = 0;
	}
	else {
		currAnim = anim;
		animations[currAnim]->ResetAnimation();
	}
}

int Sprite::GetCurrentAnim() {
	return currAnim;
}

bool Sprite::IsAnimationDone() {
	return animations[currAnim]->IsAnimationDone();
}

void Sprite::Update(double dt) {
	animations[currAnim]->Update(dt);
}

glm::ivec2 Sprite::GetFrameSize() const {
	return frameSize;
}

glm::ivec2 Sprite::GetFrameTexel(int frameNum) const {
	if (frameNum < 0 || frameNum > frameTexel.size()) {
		Engine::GetLogger().LogError(Part::Entire, "Bad frame request: " + std::to_string(frameNum));
		return { 0, 0 };
	}
	else {
		return frameTexel[frameNum];
	}
}

void Sprite::Draw() {
	ImagePtr->drawImage();
}