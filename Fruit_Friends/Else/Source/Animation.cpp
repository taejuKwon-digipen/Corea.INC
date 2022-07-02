#include <fstream>	// file input stuff
#include <filesystem>

#include "../Header/Engine.h"	// Engine::GetLogger
#include "../Header/Animation.h"

Animation::Animation() : Animation("./assets/none.anm") { }

Animation::Animation(const std::filesystem::path& fileName) : animSequenceIndex(0) {
	std::ifstream inFile(fileName);
	std::string label;

	if (fileName.extension() != ".anm") {
		throw std::runtime_error("Bad Filetype.  " + fileName.generic_string() + " not a sprite info file (.anm)");
	}
	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + fileName.generic_string());
	}

	while (inFile.eof() == false) {
		inFile >> label;
		if (label == "PlayFrame") {
			int frame;
			float targetTime;
			inFile >> frame;
			inFile >> targetTime;

			animation.push_back(new PlayFrame(frame, targetTime));
		}
		else if (label == "Loop") {
			int loopToIndex;
			inFile >> loopToIndex;
			animation.push_back(new Loop(loopToIndex));
		}
		else if (label == "End") {
			animation.push_back(new End());
		}
		else {
			Engine::GetLogger().LogError(Part::Entire,"Unknown command " + label + " in anm file " + fileName.generic_string());
		}
	}
	ResetAnimation();
}

Animation::~Animation() {
	for (CommandData* command : animation) {
		delete command;
	}
	animation.clear();
}

void Animation::Update(double dt) {
	currPlayFrameData->Update(dt);
	if (currPlayFrameData->IsFrameDone() == true) {
		currPlayFrameData->ResetTime();
		++animSequenceIndex;
		if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
			currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
		}
		else if (animation[animSequenceIndex]->GetType() == Command::Loop) {
			Loop* loopData = static_cast<Loop*>(animation[animSequenceIndex]);
			animSequenceIndex = loopData->GetLoopToIndex();
			if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
				currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
			}
			else {
				Engine::GetLogger().LogError(Part::Entire,"Loop does not go to PlayFrame");
				ResetAnimation();
			}
		}
		else if (animation[animSequenceIndex]->GetType() == Command::End) {
			isAnimationDone = true;
			return;
		}
	}
}

int Animation::GetDisplayFrame() {
	return currPlayFrameData->GetFrameNum();
}

void Animation::ResetAnimation() {
	animSequenceIndex = 0;
	currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
	isAnimationDone = false;
}

bool Animation::IsAnimationDone() {
	return isAnimationDone;
}

Animation::PlayFrame::PlayFrame(int frame, double targetTime) : frame(frame), targetTime(targetTime), timer(0) {}
void Animation::PlayFrame::Update(double dt) { timer += dt; }
bool Animation::PlayFrame::IsFrameDone() { return timer >= targetTime; }
void Animation::PlayFrame::ResetTime() { timer = 0; }
int Animation::PlayFrame::GetFrameNum() { return frame; }

Animation::Loop::Loop(int loopToIndex) : loopToIndex(loopToIndex) {}
int Animation::Loop::GetLoopToIndex() { return loopToIndex; }
