#pragma once

#include "Entity.h"

extern Sprite* human[10];

class HumanEntity : public Entity
{
private:
	int currentFrameNum;
	float timeBetweenFrames;
	float frameTimer;
public:
	
	int hp;
	int maxHP;
	std::vector<Sprite *> spriteList;

	HumanEntity();

	//Damage() returns true if we should kill this object
	bool Damage(int damage)
	{
		hp -= damage;
		if (hp < 1) return true;

		return false;
	}
	void Update(float seconds);
};

HumanEntity * MakeHuman(b2Vec2 pixelCoords, int maximumHP);