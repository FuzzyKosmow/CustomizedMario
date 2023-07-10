#pragma once
#include "GameObject.h"
#include "OverworldNode.h"
#define OVERWORLD_MARIO_BBOX_WIDTH  8
#define OVERWORLD_MARIO_BBOX_HEIGHT 8

#define ANI_ID_OVERWORLD_MARIO_SMALL 2600

#define OVERWORLD_MARIO_TRAVEL_DISTANCE_BETWEEN_NODE 30
#define OVERWORLD_MARIO_TRAVEL_SPEED 0.1

#define OVERWORLD_MARIO_AX 0.1
#define OVERWORLD_MARIO_AY 0.1

enum OverworldMovementDirection
{
	OverworldMovementDirection_Left,
	OverworldMovementDirection_Right,
	OverworldMovementDirection_Up,
	OverworldMovementDirection_Down
};

class
	COverworldMario : public CGameObject
{

	float ax = 0;
	float ay = 0;

	bool isMoving = false;
	bool isOnNode = false;
	COverworldNode* currentNode = NULL;
	float travelledDistance = 0;
	public:
	COverworldMario(float x, float y) : CGameObject(x, y) {}

	int IsCollidable() { return 1; };
	int IsBlocking() { return 1; };

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	};
 	virtual void Update(DWORD dt , vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - OVERWORLD_MARIO_BBOX_WIDTH / 2;
		t = y - OVERWORLD_MARIO_BBOX_HEIGHT / 2;
		r = x + OVERWORLD_MARIO_BBOX_WIDTH;
		b = y + OVERWORLD_MARIO_BBOX_HEIGHT;
	}
	int Move(OverworldMovementDirection direction);
	
	int GetObjectType() { return OBJECT_TYPE_MARIO_OVERWORLD; }

	void SetOnNode(COverworldNode* node) { 
		this->currentNode = node;
		if (node == NULL)
		{
			this-> isOnNode = false;
		}
		else
		this->isOnNode = true;
	
	}
	bool IsOnNode() { return this->isOnNode; }
	COverworldNode* GetCurrentNode() { return this->currentNode; }
};