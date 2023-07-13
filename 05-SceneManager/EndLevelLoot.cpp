#include "EndLevelLoot.h"



EndLevelLoot::EndLevelLoot(float x, float y) : CGameObject(x, y)
{

}


void EndLevelLoot::Update(	DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (GetTickCount64() - lastUpdate > END_LEVEL_LOOT_UPDATE_INTERVAL)
	{
		lastUpdate = GetTickCount64();

		
		if (currentLoot == END_LEVEL_LOOT_TYPE_STAR)
		{
			currentLoot = END_LEVEL_LOOT_TYPE_FLOWER;
		}
		else if ( currentLoot == END_LEVEL_LOOT_TYPE_FLOWER)
		{
			
			currentLoot = END_LEVEL_LOOT_TYPE_MUSHROOM;
			
		}
		else if (currentLoot == END_LEVEL_LOOT_TYPE_MUSHROOM)
		{
			currentLoot = END_LEVEL_LOOT_TYPE_STAR;
			
		}
		
	}
	


	CCollision::GetInstance()->Process(this, dt, coObjects);
}



void EndLevelLoot::Render()
{
	CSprites* s = CSprites::GetInstance();
	if (currentLoot == END_LEVEL_LOOT_TYPE_STAR)
	{
		s->Get(ID_SPRITE_ENDLEVEL_LOOT_STAR)->Draw(x, y);
	}
	else if (currentLoot == END_LEVEL_LOOT_TYPE_FLOWER)
	{
		s->Get(ID_SPRITE_ENDLEVEL_LOOT_FLOWER)->Draw(x, y);
	}
	else if (currentLoot == END_LEVEL_LOOT_TYPE_MUSHROOM)
	{
		s->Get(ID_SPRITE_ENDLEVEL_LOOT_MUSHROOM)->Draw(x, y);
	}
}

void EndLevelLoot::GetBoundingBox ( float &l, float &t, float &r, float &b )
{
	l = x - END_LEVEL_LOOT_BBOX_WIDTH / 2;
	t = y - END_LEVEL_LOOT_BBOX_HEIGHT / 2;
	r = x + END_LEVEL_LOOT_BBOX_WIDTH;
	b = y + END_LEVEL_LOOT_BBOX_HEIGHT;
}