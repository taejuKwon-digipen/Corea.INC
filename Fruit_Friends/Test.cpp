

#include "Test.h"

enum class Ball_anim {
	None_Anim,
	Squish_Anim,
};

Test::Test()
{}

void Test::Load()
{
	img.init("test_image/background.jpg", 0, 0, 800, 500);
}

void Test::Draw()
{
	img.drawImage();
}

void Test::Unload()
{
	
}

void Test::Update(double dt)
{
	
}
