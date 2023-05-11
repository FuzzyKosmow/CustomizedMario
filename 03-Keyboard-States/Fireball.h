#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#define ID_ANI_FIREBALL 10001
#define FIREBALL_WIDTH 16
#define START_SPEED_UP 0;
#define START_SPEED_HORIZONTAL 0.2;

class CFireball	 : public CGameObject {
public:
	CFireball(float x, float y) : CGameObject(x, y) {
		vy = START_SPEED_UP;
		vx = START_SPEED_HORIZONTAL;
	}
	void SetDirection(bool left = false);
	void Render();
	void Update(DWORD dt);
	~CFireball();
};