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
#include "Brick.h"
#include "LootBrick.h"


#define TURTLE_GRAVITY 0.001f
#define TURTLE_WALKING_SPEED 0.05f
#define TURTLE_SHELL_SPEED 0.2f
#define JUMPED_ON_OFFSET 10
#define TURTLE_DIE_BY_ATTACK_DEFLECT_VX 0.1f
#define TURTLE_DIE_BY_ATTACK_DEFLECT_VY 0.1f


#define TURTLE_BBOX_WIDTH 18
#define TURTLE_BBOX_HEIGHT 22
#define TURTLE_SHELL_BBOX_WIDTH 16
#define TURTLE_SHELL_BBOX_HEIGHT 18
#define TURTLE_BBOX_HEIGHT_DIE 7

#define TURTLE_DIE_TIMEOUT 500

#define TURTLE_STATE_WALKING 100
#define TURTLE_STATE_SHELL 200
#define TURTLE_STATE_SHELL_MOVING 300
#define TURTLE_STATE_DIE_BY_ATTACK 400

#define ANI_ID_TURLTE_WALKING_LEFT 7000
#define ANI_ID_TURLTE_WALKING_RIGHT 7001
#define ANI_ID_TURLTE_SHELL 7002
#define ANI_ID_TURLTE_SHELL_MOVING 7003



#define TURTLE_STAY_AS_SHELL_TIME 5000
class CTurtle : public CGameObject
{
protected:
	float ax;
	float ay;
	float litmitLeft;
	float litmitRight;
	ULONGLONG die_start;
	ULONGLONG shell_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void RenderBoundingBox();
	virtual int IsCollidable() { return state != TURTLE_STATE_DIE_BY_ATTACK; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	
	void OnCollisionWithLootBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithFlyingGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithFlyingTurtle(LPCOLLISIONEVENT e);
public:
	CTurtle(float x, float y, float limitLeft, float limitRight);
	virtual void SetState(int state);
	void TakeDamage();
	int GetObjectType() { return OBJECT_TYPE_TURTLE; }
	void GetLimit(float& l, float& r) { l = litmitLeft; r = litmitRight; }
};