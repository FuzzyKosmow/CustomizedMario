#pragma once
#include "GameObject.h"

#define SHROOM_GRAVITY 0.002f
#define SHROOM_WALKING_SPEED 0.05f


#define SHROOM_BBOX_WIDTH 15
#define SHROOM_BBOX_HEIGHT 15
#define SHROOM_BBOX_HEIGHT_DIE 7

#define SHROOM_DIE_TIMEOUT 500

#define SCHROOM_STATE_NOT_ACTIVATED 0
#define SHROOM_STATE_WALKING 100


#define ID_ANI_SHROOM_WALKING 6000

#define MUSHROOM_SPAWN_OFFSET 1
class CShroom : public CGameObject
{
protected:
	float ax;
	float ay;

	

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	

public:
	CShroom(float x, float y);
	void SetState(int state);
};