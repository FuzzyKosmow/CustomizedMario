#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define INACTIVE 0
#define ACTIVE 1
#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_SPAWN_IN_LOOT_OFFSET 1
class CCoin : public CGameObject {
	int activated = 1;
public:
	CCoin(float x, float y, int activate) : CGameObject(x, y) { activated = activate; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void Activate() { activated = 1; }
	int GetObjectType () { return OBJECT_TYPE_COIN; }
};