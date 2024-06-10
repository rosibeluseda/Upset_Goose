#include "BlockEntity.h"
#include "CollisionMask.h"

extern b2World *world;
extern std::vector<Sprite *> blockSprites;

BlockEntity * MakeBlock(BlockType btype, MaterialType mtype, b2Vec2 pixelCoords,
	float angleInDegrees, int maximumHP)
{
	BlockEntity * blockEntity = new BlockEntity();
	blockEntity->blockType = btype;
	blockEntity->materialType = mtype;

	b2BodyDef bodyDef;
	
	bodyDef.type = b2_dynamicBody; //make it a dynamic body i.e. one moved by physics
	bodyDef.position = Pixels2Physics(pixelCoords); //set its position in the world
	bodyDef.angle = deg2rad(angleInDegrees);

	bodyDef.angularDamping = 1.8f;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t> (blockEntity);

	blockEntity->body = world->CreateBody(&bodyDef); //create the body and add it to the world

	b2FixtureDef fixtureDef;

	//collison masking
	fixtureDef.filter.categoryBits = CMASK_BLOCK;  //this is a shot
	fixtureDef.filter.maskBits = CMASK_SHOT | CMASK_EDGES | CMASK_BLOCK | CMASK_GROUND | CMASK_ALIEN;//it collides wth lotsa stuff

	// Define a shape for our body.
	b2PolygonShape polygon;
	b2CircleShape circle;
	b2PolygonShape boxShape;

	switch (btype)
	{
	case BlockType::CONE:
	{
		
		b2Vec2 vertices[3];
		
		float cx = 0 + 50 / 2;
		float cy = 0 + 50 / 2;

		vertices[0].Set((25.f - cx) / PTM_RATIO, (cy - 0.0f) / PTM_RATIO);
		vertices[1].Set((0.0f - cx) / PTM_RATIO, (cy - 49.0f) / PTM_RATIO);
		vertices[2].Set((50.0f - cx) / PTM_RATIO, (cy - 49.0f) / PTM_RATIO);

		int32 count = 3;

		polygon.Set(vertices, count);

		fixtureDef.shape = &polygon;
	}
		break;

	case BlockType::BALL:
		circle.m_radius = 50.f / (2 * PTM_RATIO);
		fixtureDef.shape = &circle;
		break;
	case BlockType::BLOCK:
		boxShape.SetAsBox(96.0f / (2.f * PTM_RATIO), 96.0f / (2.f * PTM_RATIO));
		fixtureDef.shape = &boxShape;
		break;
	case BlockType::SHORTBLOCK:
		boxShape.SetAsBox(196.0f / (2.f * PTM_RATIO), 48.0f / (2.f * PTM_RATIO));
		fixtureDef.shape = &boxShape;
		break;
	default:
		assert(false);
		
	}//end switch(btype)

	switch (mtype)
	{
	case MaterialType::WOOD:
		fixtureDef.density = 0.3f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 0.8;
		break;
	case MaterialType::ICE:
		fixtureDef.density = 0.1f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 0.1;
		break;
	case MaterialType::CONCRETE:
		fixtureDef.density = 0.6f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 0.8;
		break;
	case MaterialType::ROCK:
		fixtureDef.density = 0.8f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 0.1;
		break;
	default:
		assert(false);
	}//end switch(mtype)

	blockEntity->body->CreateFixture(&fixtureDef);

	int numBlockTypesToSkip = (int) btype;
	int numMatTypesToSkip = (int) mtype;
	int numMaterials = (int) MaterialType::END;

	int numSpritesToSkip =  ((int)btype * 3)+(11*(int)mtype); 
	blockEntity->sprite = blockSprites[numSpritesToSkip + (int)mtype];
	blockEntity->spriteList.push_back(blockSprites[numSpritesToSkip + (int)mtype + 1]); 
	blockEntity->spriteList.push_back(blockSprites[numSpritesToSkip + (int)mtype + 2]); 

	blockEntity->maxHP = blockEntity->hp = maximumHP;

	return blockEntity;	
}

