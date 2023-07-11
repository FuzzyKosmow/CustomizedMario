#pragma once
#include "GameObject.h"

#define OVERWORLD_BLOCKING_OBJECT_BBOX_WIDTH  10
#define OVERWORLD_BLOCKING_OBJECT_BBOX_HEIGHT 10

#define ANI_ID_OVERWORLD_BUSHES 10001

class COverworldBlockingObject : public CGameObject
{
	int aniID = -1;
	int bbHeight = 0;
	int bbWidth = 0;
public:

	COverworldBlockingObject(float x, float y, int aniID, int width = OVERWORLD_BLOCKING_OBJECT_BBOX_WIDTH,int height = OVERWORLD_BLOCKING_OBJECT_BBOX_HEIGHT) : CGameObject(x, y)
	{
		this->aniID = aniID;
		this->bbHeight = height;
		this->bbWidth = width;
	}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; };
	void Render()
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(aniID)->Render(x, y);
		RenderBoundingBox();
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - bbWidth / 2;
		t = y - bbHeight / 2;
		r = x + bbWidth;
		b = y + bbHeight;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	int GetObjectType() { return OBJECT_TYPE_OVERWORLD_BLOCKING_OBJECT; }
};
