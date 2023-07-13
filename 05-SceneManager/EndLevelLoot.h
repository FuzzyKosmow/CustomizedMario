#pragma once
#include "GameObject.h"


#define ID_SPRITE_ENDLEVEL_LOOT_MUSHROOM		600101
#define ID_SPRITE_ENDLEVEL_LOOT_FLOWER			600102
#define ID_SPRITE_ENDLEVEL_LOOT_STAR			600103

#define END_LEVEL_LOOT_BBOX_WIDTH				16
#define END_LEVEL_LOOT_BBOX_HEIGHT				16

#define END_LEVEL_LOOT_TYPE_MUSHROOM			1
#define END_LEVEL_LOOT_TYPE_FLOWER				2
#define END_LEVEL_LOOT_TYPE_STAR				3

#define END_LEVEL_LOOT_UPDATE_INTERVAL			300
#define END_LEVEL_LOOT_GENERAL_SCORE			6900

class EndLevelLoot : public CGameObject
{
	int currentLoot = END_LEVEL_LOOT_TYPE_FLOWER;

	ULONGLONG lastUpdate = 0;
public:
	EndLevelLoot(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update (DWORD dt, vector<LPGAMEOBJECT>* coObjects);




	int GetCurrentLoot() const { return currentLoot; }

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	int GetObjectType() { return OBJECT_TYPE_END_LEVEL_LOOT; }
};