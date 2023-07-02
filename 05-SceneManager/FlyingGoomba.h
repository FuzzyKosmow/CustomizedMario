
#pragma once
#include "GameObject.h"

#define FLYING_GOOMBA_FLYING_GRAVITY 0.0005f
#define FLYING_GOOMBA_WALKING_GRAVITY 0.002f

#define FLYING_GOOMBA_WALKING_SPEED 0.05f
#define FLYING_GOOMBA_JUMP_SPEED 0.1f

#define FLYING_GOOMBA_DEFLECT_SPEED 0.2f
#define FLYING_GOOMBA_BBOX_WIDTH 16
#define FLYING_GOOMBA_BBOX_HEIGHT 20
#define FLYING_GOOMBA_BBOX_HEIGHT_DIE 7

#define FLYING_GOOMBA_DIE_TIMEOUT 500

#define FLYING_GOOMBA_STATE_FLYING 100
#define FLYING_GOOMBA_STATE_WALKING 200
#define FLYING_GOOMBA_STATE_DIE 300


#define ID_ANI_FLYING_GOOMBA_FLYING 5003
#define ID_ANI_FLYING_GOOMBA_WALKING 5004
#define ID_ANI_FLYING_GOOMBA_DIE 5005

#define FLYING_GOOMBA_TIME_BETWEEN_JUMP 300
#define FLYING_GOOMBA_JUMP_COUNT 3
#define FLYING_GOOMBA_JUMP_SERIES_COOLDOWN FLYING_GOOMBA_TIME_BETWEEN_JUMP*FLYING_GOOMBA_JUMP_COUNT*2

class CFlyingGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	bool jump_series_started = false;
	bool isOnPlatform = false;
	int jump_count = 0;

	ULONGLONG die_start;
	ULONGLONG jump_series_start = 0;
	ULONGLONG last_jump = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state != FLYING_GOOMBA_STATE_DIE; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFlyingGoomba(float x, float y);
	virtual void SetState(int state);
	int GetObjectType () { return OBJECT_TYPE_FLYING_GOOMBA; }
};