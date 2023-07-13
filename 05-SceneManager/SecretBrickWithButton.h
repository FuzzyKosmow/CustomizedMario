#pragma once
#include "Brick.h"
#include "Detection.h"
#include "GroundButton.h"
#include "Coin.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define SECRET_BRICK_WITH_BUTTON_STATE_NORMAL 0
#define SECRET_BRICK_WITH_BUTTON_STATE_SHOW_BUTTON	1



#define SECRET_BRICK_WITH_BUTTON_ANI_NORMAL	10003
#define SECRET_BRICK_WITH_BUTTON_ANI_SHOW_BUTTON 10002


#define SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_X 0
#define SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_Y -16.0f

#define SECRET_BRICK_WITH_BUTTON_DETECTION_ZONE_WIDTH 5
#define SECRET_BRICK_WITH_BUTTON_DETECTION_ZONE_HEIGHT 5

#define SECRET_BRICK_WITH_BUTTON_BREAK_SCORE 420
using namespace std;

class ObjectDetector;

class CSecretBrickWithButton : public CBrick
{
	CGroundButton* button = NULL;
	bool convertedBrickToCoin = false;
	ObjectDetector* detector = NULL;
public:
	CSecretBrickWithButton(float x, float y);
	void SetState (int state) ;
	void OnCollisionWith (LPCOLLISIONEVENT e);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int GetObjectType() {
		return OBJECT_TYPE_SECRET_BRICK_WORLD_1_1;
	}
	void Break()
	{
		if (state == SECRET_BRICK_WITH_BUTTON_STATE_NORMAL)
		{
			SetState (SECRET_BRICK_WITH_BUTTON_STATE_SHOW_BUTTON);
			HUD::GetInstance()->PopUpScoreAtMario(SECRET_BRICK_WITH_BUTTON_BREAK_SCORE);
		}
		
	}
};
