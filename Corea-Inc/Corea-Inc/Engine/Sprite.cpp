// Taeju Kwon
#include "Engine.h"
#include "Sprite.h"
#include "Animation.h"
#include "ComponentManager.h"
#include "GameObject.h"
#include "Image.h"
#include "Rect.h"
#include "MatrixOperator.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>

coconut::Sprite::Sprite(const std::filesystem::path& spriteIntoFile, GameObject* object)
{
	Load(spriteIntoFile, object);
}

coconut::Sprite::~Sprite()
{
	for (Animation* anim : animations)
	{
		delete anim;
	}
	animations.clear();
}

void coconut::Sprite::Load(const std::filesystem::path& spriteIntoFile, GameObject* object)
{
	animations.clear();
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteIntoFile.extension() != ".spt")
	{
		throw std::runtime_error("Bad Filetype: " + spriteIntoFile.generic_string());
	}

	std::ifstream inFile(spriteIntoFile);

	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to load " + spriteIntoFile.generic_string());
	}

	std::string text;
	inFile >> text;
	const char* Imagetext = text.c_str();
	ImagePtr = Engine::GetImageManager().Load(Imagetext);
	frameSize = ImagePtr->GetSize();

	inFile >> text;

	while (inFile.eof() == false)
	{
		if (text == "FrameSize")
		{
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames")
		{
			int numFrames;
			inFile >> numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++)
			{
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame")
		{
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot")
		{
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else if (text == "Anim")
		{
			inFile >> text;
			animations.push_back(new Animation(text));
		}
		else
		{
			// Engine::GetLogger().LogError(Part::Entire, "Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true)
	{
		frameTexel.push_back({ 0, 0 });
	}
	if (animations.empty() == true)
	{
		animations.push_back(new Animation());
		PlayAnimation(0);
	}
}

glm::ivec2 coconut::Sprite::GetHotSpot(int index)
{
	if (index >= hotSpotList.size())
	{
		// Engine::GetLogger().LogError(Part::Entire, "Sprite is missing hotspot index: " + std::to_string(index);
		return { 0, 0 };
	}
	return hotSpotList[index];
}

void coconut::Sprite::PlayAnimation(int anim)
{
	if (anim < 0 || anim >= animations.size())
	{
		// Engine::GetLogger().LogError(Part::Entire, "Animation " + std::to_string(anim) + " not found.");
		currAnim = 0;
	}
	else
	{
		currAnim = anim;
		animations[currAnim]->ResetAnimation();
	}
}

int coconut::Sprite::GetCurrentAnim()
{
	return currAnim;
}

bool coconut::Sprite::IsAnimationDone()
{
	return animations[currAnim]->IsAnimationDone();
}

void coconut::Sprite::Update(double dt)
{
	animations[currAnim]->Update(dt);
}

void coconut::Sprite::Draw(math::TransformMatrix displayMatrix)
{
	ImagePtr->drawImage();
}

glm::ivec2 coconut::Sprite::GetFrameSize() const
{
	return frameSize;
}

glm::ivec2 coconut::Sprite::GetFrameTexel(int frameNum) const
{
	if (frameNum < 0 || frameNum > frameTexel.size())
	{
		// Engine::GetLogger().LogError(Part::Entire, "Bad frmae request: " + std::to_string(frameNum));
		return { 0, 0 };
	}
	else
	{
		return frameTexel[frameNum];
	}
}