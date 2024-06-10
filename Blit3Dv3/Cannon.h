#pragma once

#include "Blit3D.h"
#include "Physics.h"
extern Sprite* cauchera[8];
extern bool activeSlingShot;

class Cannon
{
private:
	int currentFrameNum;
	float timeBetweenFrames;
	float frameTimer;
public:
	b2Vec2 positionPixels;
	float angle;
	Sprite* sprite;
	float rotateDir;
	std::vector<Sprite*> spriteList;
	Cannon();

	void Update(float seconds);
	void Draw();
};






