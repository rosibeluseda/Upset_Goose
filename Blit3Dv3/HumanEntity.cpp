#include "HumanEntity.h"
#include "CollisionMask.h"

extern b2World* world;

HumanEntity::HumanEntity()
{
	typeID = ENTITYHUMAN;
	maxHP = hp = 50;

	for (int i = 0; i < 10; i++)
	{
		spriteList.push_back(human[i]);
	}
	currentFrameNum = 0;
	sprite = spriteList[currentFrameNum];

	timeBetweenFrames = 1.0f / 10;
	frameTimer = 0;

}

void HumanEntity::Update(float seconds)
{
	frameTimer += seconds;
	//is it time to advance frames?
	while (frameTimer >= timeBetweenFrames)
	{
		frameTimer -= timeBetweenFrames;
		currentFrameNum++;
		if (currentFrameNum > 10) //loop the animation frames
			currentFrameNum = 0;

		sprite = spriteList[currentFrameNum];
	}

}

HumanEntity* MakeHuman(b2Vec2 pixelCoords, int maximumHP)
{
	HumanEntity* humanEntity = new HumanEntity();

	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody; //make it a dynamic body i.e. one moved by physics
	bodyDef.position = Pixels2Physics(pixelCoords); //set its position in the world
	bodyDef.angle = deg2rad(0);

	bodyDef.angularDamping = 1.8f;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t> (humanEntity);

	humanEntity->body = world->CreateBody(&bodyDef); //create the body and add it to the world

	b2FixtureDef fixtureDef;

	//collison masking
	fixtureDef.filter.categoryBits = CMASK_ALIEN;  //this is a shot
	fixtureDef.filter.maskBits = CMASK_SHOT | CMASK_BLOCK;


	// Define a shape for our body.
	
	b2PolygonShape boxShape;
	//w 36  h 75
	boxShape.SetAsBox(40.0f / (2.f * PTM_RATIO), 70.0f / (2.f * PTM_RATIO));
	fixtureDef.shape = &boxShape;

	humanEntity->body->CreateFixture(&fixtureDef);

	humanEntity->body->SetBullet(true);

	for (int i = 0; i < 10; i++)
	{
		humanEntity->spriteList.push_back(human[i]);
	}
	humanEntity->sprite = humanEntity->spriteList[0];

	humanEntity->maxHP = humanEntity->hp = 50;

	return humanEntity;

}
