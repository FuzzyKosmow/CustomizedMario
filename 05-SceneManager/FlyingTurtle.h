#pragma once
#include "GameObject.h"


#pragma once
#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"
#include "Mario.h"
#include "Goomba.h"
#include "Textures.h"

#include "LootBrick.h"


#define FLYING_TURTLE_GRAVITY 0.001f
#define FLYING_TURTLE_FLYING_GRAVITY 0.0005f

#define FLYING_TURTLE_WALKING_SPEED 0.05f
#define FLYING_TURTLE_JUMP_SPEED 0.1f
#define FLYING_TURTLE_SHELL_SPEED 0.2f

#define JUMPED_ON_OFFSET 10

#define FLYING_TURTLE_DIE_BY_ATTACK_DEFLECT_VX 0.1f
#define FLYING_TURTLE_DIE_BY_ATTACK_DEFLECT_VY 0.1f

#define FLYING_TURTLE_BBOX_WIDTH 18
#define FLYING_TURTLE_BBOX_HEIGHT 20
#define FLYING_TURTLE_SHELL_BBOX_WIDTH 16
#define FLYING_TURTLE_SHELL_BBOX_HEIGHT 18
#define FLYING_TURTLE_BBOX_HEIGHT_DIE 7

#define FLYING_TURTLE_DIE_TIMEOUT 500

#define FLYING_TURTLE_STATE_DIE 0
#define FLYING_TURTLE_STATE_FLYING 100
#define FLYING_TURTLE_STATE_WALKING 200
#define FLYING_TURTLE_STATE_SHELL 300
#define FLYING_TURTLE_STATE_SHELL_MOVING 400
#define FLYING_TURTLE_STATE_DIE_BY_ATTACK 500

#define ANI_ID_FLYING_TURTLE_WALKING_LEFT 7000
#define ANI_ID_FLYING_TURTLE_WALKING_RIGHT 7001
#define ANI_ID_FLYING_TURTLE_SHELL 7002
#define ANI_ID_FLYING_TURTLE_SHELL_MOVING 7003

#define ANI_ID_FLYING_TURTLE_FLYING_RIGHT 7004
#define ANI_ID_FLYING_TURTLE_FLYING_LEFT 7005

#define FLYING_FLYING_TURTLE_TIME_BETWEEN_JUMP 300
#define FLYING_FLYING_TURTLE_JUMP_COUNT 3
#define FLYING_FLYING_TURTLE_JUMP_SERIES_COOLDOWN FLYING_FLYING_TURTLE_TIME_BETWEEN_JUMP*FLYING_FLYING_TURTLE_JUMP_COUNT*2

#define FLYING_TURTLE_STAY_AS_SHELL_TIME 5000
class CFlyingTurtle : public CGameObject
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
	ULONGLONG shell_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void RenderBoundingBox();
	virtual int IsCollidable() { return state != FLYING_TURTLE_STATE_DIE_BY_ATTACK; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFlyingTurtle(float x, float y);
	virtual void SetState(int state);
	int GetObjectType() { return OBJECT_TYPE_FLYING_TURTLE; }
};