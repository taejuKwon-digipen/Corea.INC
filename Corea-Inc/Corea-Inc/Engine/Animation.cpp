// Taeju Kwon
#include <fstream>
#include <filesystem>
#include "Engine.h"
#include "Animation.h"

coconut::Animation::Animation() : Animation("./assets/none.nam") {}

coconut::Animation::Animation(const std::filesystem::path& fileName) : animSequenceIndex(0)
{
	std::ifstream inFile(fileName);
	std::string label;

	if (fileName.extension() != ".anm")
	{
		throw::std::runtime_error("Bad file type: " + fileName.generic_string());
	}
	if (inFile.is_open() == false)
	{
		throw::std::runtime_error("Failed to load: " + fileName.generic_string());
	}

	while (inFile.eof() == false)
	{
		inFile >> label;
		if(label == "PlayFrame")
		{
			int frame;
			float targetTime;
			inFile >> frame;
			inFile >> targetTime;

			animation.push_back(new PlayFrame(frame, targetTime));
		}
		else if (label == "Loop")
		{
			int loopToIndex;
			inFile >> loopToIndex;
			animation.push_back(new Loop(loopToIndex));
		}
		else if (label == "End")
		{
			animation.push_back(new End());
		}
		else
		{
			Engine::GetLogger().LogError(Part::Entire, "Unknown command " + label + " in anm file " + fileName.generic_string());
		}
		ResetAnimation();
	}
}

coconut::Animation::~Animation()
{
	for (CommandData* command : animation)
	{
		delete command;
	}
	animation.clear();
}

void coconut::Animation::Update(double dt)
{
	currPlayFrameData->Update(dt);
	if (currPlayFrameData->IsFrameDone() == true)
	{
		currPlayFrameData->ResetTime();
		++animSequenceIndex;
		if (animation[animSequenceIndex]->GetType() == Command::PlayFrame)
		{
			currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
		}
		else if (animation[animSequenceIndex]->GetType() == Command::Loop)
		{
			Loop* loopData = static_cast<Loop*>(animation[animSequenceIndex]);
			animSequenceIndex = loopData->GetLoopToIndex();
			if (animation[animSequenceIndex]->GetType() == Command::PlayFrame)
			{
				currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
			}
			else
			{
				// Engine::GetLogger().LogError(Part::Entire, "Loop does not go to PlayFrame");
				ResetAnimation();
			}
		}
		else if (animation[animSequenceIndex]->GetType() == Command::End)
		{
			isAnimationDone = true;
			return;
		}
	}
}

int coconut::Animation::GetDisplayFrame()
{
	return currPlayFrameData->GetFrameNum();
}

void coconut::Animation::ResetAnimation()
{
	animSequenceIndex = 0;
	currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
	isAnimationDone = false;
}

bool coconut::Animation::IsAnimationDone()
{
	return isAnimationDone;
}

coconut::Animation::PlayFrame::PlayFrame(int frame, double duration) : frame(frame), targetTime(duration), timer(0) {}
void coconut::Animation::PlayFrame::Update(double dt) {	timer += dt; }
bool coconut::Animation::PlayFrame::IsFrameDone() {	return timer >= targetTime; }
void coconut::Animation::PlayFrame::ResetTime() { timer = 0; }
int coconut::Animation::PlayFrame::GetFrameNum() { return frame; }

coconut::Animation::Loop::Loop(int loopToIndex) : loopToIndex(loopToIndex) {}
int coconut::Animation::Loop::GetLoopToIndex() { return loopToIndex; }
