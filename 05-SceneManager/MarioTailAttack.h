#pragma once
#include "GameObject.h"





//What it does is render a bounding box according to mario direction and pos x,y . Then handle collision with other objects
class CMarioTailAttack : public CGameObject
{
	float ax = 0.0000001;
	float ay = 0.0000001; //Place holder properties
	bool isActive = false;
	int direction;
	ULONGLONG raccoonAttackStart = -1;
	LPGAMEOBJECT player;
public:
	CMarioTailAttack(float x, float y);
	
	void Attack(int x, ULONGLONG time);
	int IsCollidable() { return isActive; }
	int IsBlocking () { return 0; }
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Attack(int dir = 1);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int GetObjectType() { return OBJECT_TYPE_MARIO_TAIL_ATTACK; }
	int IsStatic () { return 1; }
};