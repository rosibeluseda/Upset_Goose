#include "Cannon.h"
#include "CollisionMask.h"

Cannon::Cannon()
{
	positionPixels = b2Vec2(0, 0);
	angle = 0;
	sprite = NULL;
	rotateDir = 0;

	for (int i = 0; i < 8; i++)
	{
		spriteList.push_back(cauchera[i]);
	}
	currentFrameNum = 0;
	sprite = spriteList[currentFrameNum];

	timeBetweenFrames = 1.0f / 10;
	frameTimer = 0;
}

void Cannon::Update(float seconds)
{
	angle += rotateDir * seconds * 20;
	if (angle < 0) angle = 0;
	if (angle > 20) angle = 20;

}

void Cannon::Draw()
{
	sprite->angle = angle;
	sprite->Blit(positionPixels.x, positionPixels.y);
}


