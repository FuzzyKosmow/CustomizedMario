#pragma once
#include "GameObject.h"
#define DEADTHBLOCK_BBOX_WIDTH  30
#define DEADTHBLOCK_BBOX_HEIGHT 16
class DeathBlock : public CGameObject
{
	float customWidth = 0;
	float customHeight = 0;
public:
DeathBlock(float x, float y, float width = DEADTHBLOCK_BBOX_WIDTH, float height = DEADTHBLOCK_BBOX_HEIGHT);
		~DeathBlock();
		virtual void Render();
		virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
		int IsCollidable() { return 1; };
		int IsBlocking() { return 0; };
		void OnCollisionWith(LPCOLLISIONEVENT e);
		void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
		void RenderBoundingBox();

		int GetObjectType() { return OBJECT_TYPE_DEATH_BLOCK; }
};