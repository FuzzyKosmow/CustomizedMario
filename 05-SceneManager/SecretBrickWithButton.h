#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "GroundButton.h"
//


#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define SECRET_BRICK_WITH_BUTTON_STATE_NORMAL 0
#define SECRET_BRICK_WITH_BUTTON_STATE_SHOW_BUTTON	1
#define SECRET_BRICK_WITH_BUTTON_STATE_HIT_BUTTON 2


#define SECRET_BRICK_WITH_BUTTON_ANI_NORMAL	0
#define SECRET_BRICK_WITH_BUTTON_ANI_SHOW_BUTTON	1
#define SECRET_BRICK_WITH_BUTTON_ANI_HIT_BUTTON 2

#define SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_X 8
#define SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_Y 8

class CSecretBrickWithButton : public CBrick
{
	CGroundButton* button = NULL;
	bool convertedBrickToCoin = false;
public:
	CSecretBrickWithButton(float x, float y) : CBrick(x, y) {
		state =  SECRET_BRICK_WITH_BUTTON_STATE_NORMAL;
	};
	void SetState (int state) ;
	void OnCollisionWith (LPCOLLISIONEVENT e);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};
