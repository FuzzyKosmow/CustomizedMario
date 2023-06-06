#pragma once
#include "LootBrick.h"

void CLootBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (lootState == LOOT_BRICK_STATE_NOT_LOOTED) {
		animations->Get(ID_ANI_LOOT_BRICK)->Render(x, y);
	}
	else if (lootState == LOOT_BRICK_STATE_LOOTED) {
		animations->Get(ID_ANI_LOOT_BRICK_LOOTED)->Render(x, y);
	}
	//RenderBoundingBox();
}

void CLootBrick::SpawnLoot()
{
	//Do nothing for now

	
}

void CLootBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CLootBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	
}