#pragma once
#include "GameObject.h"


//THERE IS A HIDDEN THING BETWEEN HEIGHT AND WID OF A SPRITE, FOR SOME REASON IT CAN CAUSE BLUR IF REDUCE / INCREASE BY 1. TRY INCREASE OR DECREASE BY 1 PIXEL IN HEIGHT
#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.0003f
#define MARIO_ACCEL_FLY_X 0.0003f
#define MARIO_ACCEL_FLY_Y 0.0003f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_RACCOON_FLY_SPEED_Y	0.3f
#define MARIO_RACCOON_FLY_SPEED_X	0.1f
#define MARIO_RACCOON_JUMP_INVERVAL_REQUIRED 300
#define MARIO_RACCOON_MAX_FLY_VY_PHASE_1	0.6f //Still on the ground , allow to jump press space again within interval to transition to fly and limit speed
#define MARIO_RACCOON_MAX_FLY_VY_PHASE_2	0.15f
#define MARIO_RACCOON_DESCEND_MAX_DROP_VY	0.1f

#define	MARIO_DROP_DISTANCE_FOR_CAMERA		100


#define MARIO_MAX_DROP_SPEED	0.2f
#define MARIO_RACCOON_GRAVITY	0.0005f
#define MARIO_GRAVITY			0.002f
#define MARIO_RACCOON_LIFT_GRAVITY	0.0019f

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
#define MARIO_STATE_FACING_FRONT	900
#define MARIO_ENDING_MOVE_RIGHT 1000
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

#define ID_ANI_MARIO_RACCOON_FLYING_RIGHT 2510
#define ID_ANI_MARIO_RACCOON_FLYING_LEFT 2511
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


//Death to overworld stats
#define MARIO_DIE_TIME 1000
#define MARIO_DIM_TIME	500
#define MARIO_DELAY_TIME 1000
#define MARIO_UNDIM_TIME	0

//Move to back to overworld after completetting level
#define MARIO_WALK_TIME_BEFORE_DIME	2500



//Score value to be used when adding
#define SCORE_MINI	10
#define SCORE_DEFAULT_ADD	100
#define SCORE_COIN 50	
#define SCORE_TURTLE_KILL	300
#define SCORE_GOOMBA_KILL	200
#define SCORE_FLYING_GOOMBA_KILL	200
#define SCORE_MUSHROOM	500
#define SCORE_GREEN_MUSHROOM	1000
#define SCORE_LEAF	1000
#define SCORE_JUMP_ON	100

#define SCORE_MAX	9999999
#define LIVES_MAX	99
#define COIN_MAX	99
#define LIVE_VALUE_START 4
class CMarioTailAttack;

class CMario : public CGameObject
{
	
	BOOLEAN isSitting;
	bool isFlying = false;
	bool isDescending = false;
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
	CMarioTailAttack* tailAttack;
	int coin;
	//Raccoon attack
	ULONGLONG raccoonAttack_start;
	bool isRaccoonAttacking = false;
	//Flying
	ULONGLONG lastJumpPressed = 0;
	bool flyTookOff = false;
	ULONGLONG flyTookOffStart = 0;
	float vyFlyMax = MARIO_RACCOON_MAX_FLY_VY_PHASE_1;

	//If mario is standing on top of a travelable tunnel, set this to true
	bool isOnTravelableTunnel = false;
	LPGAMEOBJECT travelableTunnel = NULL;
	
	
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);

	void OnCollisionWithBrick (LPCOLLISIONEVENT e);
	void OnCollisionWithLootBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithSchroom(LPCOLLISIONEVENT e);
	
	void OnCollisionWithDetectionBox(LPCOLLISIONEVENT e);
	void OnCollisionWithPlantBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);

	void OnCollisionWithGroundButton(LPCOLLISIONEVENT e);

	void OnCollisionWithEatingPlant( LPCOLLISIONEVENT e);


	void OnCollisionWithFlyingGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithFlyingTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithEndLevelLoot(LPCOLLISIONEVENT e);


	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();
	bool colliable = true;
	ULONGLONG uncolliableTime = 0;
	ULONGLONG uncolliableStart = 0;
	bool hasJustSetUncolliable = false;


	//Drop distance when mario is falling
float dropDistance = 0;
	

	//To overworld stats
	ULONGLONG dead_start = 0;
	ULONGLONG dim_start = 0;
	bool deadDimmed = false;
	bool deadTimerStarted = false;

	//Compelted level stats
	ULONGLONG end_level_walk_start = 0;
	bool endLevelDimmed = false;

	bool levelFinished = false;
	bool sceneSwitchActivated = false;

	//Score and lives
	int score = 0;
	int lives = LIVE_VALUE_START;
	//Items
	vector<int> items = vector<int>(MARIO_MAX_ITEMS, 0);
public:
	
	
	CMario(float x, float y);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void SetUnColliableFor(ULONGLONG time)
	{
			colliable = false;
		uncolliableTime = time;
		uncolliableStart = GetTickCount64();
		hasJustSetUncolliable = true;
	}
	void SetColliable() { colliable = true; }
	void SetUncolliable() { colliable = false; }
	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE && colliable);
	}

	int IsBlocking() { return 0; }
	bool IsFlying() { return isFlying; }
	void OnNoCollision(DWORD dt);
	//All collision is proactive, meaning for this to be called the object must be moving, apparently
	void OnCollisionWith(LPCOLLISIONEVENT e);
	
	void SetLevel(int l);
	int GetLevel() { return level; };
	int GetXDirection() { return nx; }; //X > 0: right, X < 0: left
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void AddCoin(int num) { 
		//No more than 99
		if (coin + num > COIN_MAX)
			coin = COIN_MAX;
		else
			coin += num;
	}
	int GetLive() { return lives; }
	void AddLive(int num) { 
		//No more than 99
		if (lives + num > LIVES_MAX)
			lives = LIVES_MAX;
		else
			lives += num;
	}
	void MinusLive() { 
		//No less than 0
		if (lives - 1 < 0)
			lives = 0;
		else
			lives -= 1;
	}
	int GetCoin() { return coin; }
	int GetScore() { return score; }
	void AddScoreWithPopUp(int num);
	void AddScore(int num) { 
		//No more than 9999999. Because of rendering
		if (score + num > SCORE_MAX)
			score = SCORE_MAX;
		else
			score += num;

	}
	void DisplaceHoldObject()
	{
		holdingObject = false;
		holdObject = NULL;
	}
	LPGAMEOBJECT GetHoldObject() { return holdObject; }
	float GetDropDistance() { return dropDistance; }
	void TakeDamage(); // 1 unit of damage = 1 level

	bool IsDescending() { return isDescending; }

	//Travelling between place/scenes
	bool OnTravelableTunnel() { return isOnTravelableTunnel; }
	void SetOnTravelableTunnel(bool b) { isOnTravelableTunnel = b; }
	LPGAMEOBJECT GetTravelableTunnel() { return travelableTunnel; }
	void SetTravelableTunnel(LPGAMEOBJECT t) { travelableTunnel = t; }

	float SpeedXRatio() { return abs(vx) / abs(MARIO_RUNNING_SPEED); }

	///
	int GetObjectType () { return OBJECT_TYPE_MARIO; }
};


