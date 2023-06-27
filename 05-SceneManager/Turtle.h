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


#define TURTLE_GRAVITY 0.001f
#define TURTLE_WALKING_SPEED 0.05f
#define TURTLE_SHELL_SPEED 0.2f
#define JUMPED_ON_OFFSET 10

#define TURTLE_BBOX_WIDTH 18
#define TURTLE_BBOX_HEIGHT 22
#define TURTLE_SHELL_BBOX_WIDTH 16
#define TURTLE_SHELL_BBOX_HEIGHT 18
#define TURTLE_BBOX_HEIGHT_DIE 7

#define TURTLE_DIE_TIMEOUT 500

#define TURTLE_STATE_WALKING 100
#define TURTLE_STATE_SHELL 200
#define TURTLE_STATE_SHELL_MOVING 300

#define ANI_ID_TURLTE_WALKING_LEFT 7000
#define ANI_ID_TURLTE_WALKING_RIGHT 7001
#define ANI_ID_TURLTE_SHELL 7002
#define ANI_ID_TURLTE_SHELL_MOVING 7003

class CTurtle : public CGameObject
{
protected:
	float ax;
	float ay;
	float litmitLeft;
	float litmitRight;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void RenderBoundingBox();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CTurtle(float x, float y, float limitLeft, float limitRight);
	virtual void SetState(int state);
};