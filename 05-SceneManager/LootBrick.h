#pragma once
#include "Brick.h"

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LOOT_BRICK 10001
#define ID_ANI_LOOT_BRICK_LOOTED 10002
#define ID_ANI_LOOT_BRICK_TYPE_BRICK 10003

#define BRICK_WIDTH 16
#define LBRICK_BBOX_WIDTH 17
#define LBRICK_BBOX_HEIGHT 17

#define LOOT_TYPE_NONE 0//Nothing.
#define LOOT_TYPE_MUSHROOM 1 //Mario big.
#define LOOT_TYPE_LEAF 2 //Mario raccoon.
#define LOOT_TYPE_COIN 3 //Coin 

#define LOOT_BRICK_STATE_NOT_LOOTED 100
#define LOOT_BRICK_STATE_LOOTED 200

#define LOOT_BRICK_TIME_TO_SHOW_LOOT 600
#define LOOT_BRICK_TIME_TO_SHOW_COIN 150
#define BRICK_AND_LOOT_HEIGHT_DIFF 30
#define BRICK_AND_COIN_HEIGHT_DIFF 50


#define LOOT_BRICK_SPRITE_TYPE_QUESTION_MARK 0 //NULL
#define LOOT_BRICK_SPRITE_TYPE_BRICK 1

class CLootBrick : public CGameObject {
	public:

	int lootType;
	int lootState;
	LPGAMEOBJECT loot = NULL;
	ULONGLONG timeStartToShowLoot = 0;
	bool lootShowComplete = false;
	
	int spriteType = LOOT_BRICK_SPRITE_TYPE_QUESTION_MARK;
	CLootBrick(float x, float y, int lootType) : CGameObject(x, y) {
		
		
		this->lootType = lootType;
		lootState = LOOT_BRICK_STATE_NOT_LOOTED;
	}
	
	void Render();
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state) { lootState = state; };
	int GetCurrentState() { return lootState; };

	void SetLoot(LPGAMEOBJECT gameLoot) { loot = gameLoot; };
	
	void ShowLoot(); //Slowly move it to the top then enable it.
	void EnableLoot();

	int GetLootState () { return lootState; };
	void SetSpriteType(int spriteType) { this->spriteType = spriteType; };
	int GetObjectType () { return OBJECT_TYPE_LOOT_BRICK; };
};

