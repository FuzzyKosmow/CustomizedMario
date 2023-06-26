#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

//THERE IS A HIDDEN THING BETWEEN HEIGHT AND WID OF A SPRITE, FOR SOME REASON IT CAN CAUSE BLUR IF REDUCE / INCREASE BY 1. TRY INCREASE OR DECREASE BY 1 PIXEL IN HEIGHT
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_ACCEL_FLY_X 0.0003f
#define MARIO_ACCEL_FLY_Y 0.0003f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_RACCOON_FLY_SPEED_Y	0.4f
#define MARIO_RACCOON_FLY_SPEED_X	0.1f

#define MARIO_RACCOON_GRAVITY	0.0005f
#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f
#define MARIO_RACCOON_ATTACK_TIME 300

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
//RACCON STATE
#define MARIO_STATE_FLY_RIGHT		700
#define MARIO_STATE_FLY_LEFT		701
#define MARIO_STATE_TAIL_ATTACK_RIGHT	800
#define MARIO_STATE_TAIL_ATTACK_LEFT	801

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401
#define ID_ANI_MARIO_IDLE_RIGHT_GRABBING 410
#define ID_ANI_MARIO_IDLE_LEFT_GRABBING 411


#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501
#define ID_ANI_MARIO_WALKING_RIGHT_GRABBING 510
#define ID_ANI_MARIO_WALKING_LEFT_GRABBING 511

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIOR_RUNNING_RIGHT_GRABBING 610
#define ID_ANI_MARIOR_RUNNING_LEFT_GRABBING 611

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_JUMP_RUN_RIGHT_GRABBING 810
#define ID_ANI_MARIO_JUMP_RUN_LEFT_GRABBING 811

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT_GRABBING 1110
#define ID_ANI_MARIO_SMALL_IDLE_LEFT_GRABBING 1111



#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201
#define ID_ANI_MARIO_SMALL_WALKING_RIGHT_GRABBING 1210
#define ID_ANI_MARIO_SMALL_WALKING_LEFT_GRABBING 1211

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301
#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT_GRABBING 1310
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT_GRABBING 1311



#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601
#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT_GRABBING 1610
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT_GRABBING 1611



//RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 1701
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT_GRABBING 1710
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT_GRABBING 1711


#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 1801
#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT_GRABBING 1810
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT_GRABBING 1811


#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 1901
#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT_GRABBING 1910
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT_GRABBING 1911


#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2000
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2001

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2100
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2101

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 2200
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 2201
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_GRABBING 2210
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_GRABBING 2211

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2301
//Mid air brace
#define ID_ANI_MARIO_RACCOON_FLY_RIGHT 2400
#define ID_ANI_MARIO_RACCOON_FLY_LEFT 2401
//Attack
#define ID_ANI_MARIO_RACCOON_ATTACK_RIGHT 2500
#define ID_ANI_MARIO_RACCOON_ATTACK_LEFT 2501

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_RACCOON_BBOX_WIDTH  15
#define MARIO_RACCOON_BBOX_HEIGHT 24

#define MARIO_RACCOON_SITTING_BBOX_WIDTH  14
#define MARIO_RACCOON_SITTING_BBOX_HEIGHT 16
#define MARIO_RACCOON_BBOX_WIDTH_OFFSET 2
#define MARIO_RACCOON_BBOX_HEIGHT_OFFSET 0

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	bool isFlying = false;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int untouchable;
	

	bool maxSpeedReached = false;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;


	bool holdingObject = false;
	LPGAMEOBJECT holdObject = nullptr;
	/*CMarioTailAttack tailAttack;*/
	int coin;
	//Raccoon attack
	ULONGLONG raccoonAttack_start;
	bool isRaccoonAttacking = false;
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithLootBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithSchroom(LPCOLLISIONEVENT e);
	
	void OnCollisionWithDetectionBox(LPCOLLISIONEVENT e);
	void OnCollisionWithPlantBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithEatingPlant( LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	bool colliable = true;
	ULONGLONG toBeColliableAgainAt;
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		raccoonAttack_start = -1;

	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void SetUnColliableFor(ULONGLONG time) { colliable = false; toBeColliableAgainAt = GetTickCount64() + time; }
	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE && colliable);
	}

	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	//All collision is proactive, meaning for this to be called the object must be moving, apparently
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; };
	int GetXDirection() { return nx; }; //X > 0: right, X < 0: left
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void AddCoin(int num) { coin += num; }
	void TakeDamage(); // 1 unit of damage = 1 level
	
};

class CMarioTailAttack : public CGameObject
{
	bool isRendered = false;


public:
	CMarioTailAttack(float x, float y) : CGameObject(x, y)
	{

	}
	CMarioTailAttack()
	{

	}
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool GetRenderState() { return isRendered; };
	bool SetRenderState(bool value) { isRendered = value; };
	
	

};