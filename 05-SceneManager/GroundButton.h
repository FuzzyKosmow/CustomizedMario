#pragma once
#include "GameObject.h"


#define GROUND_BUTTON_BBOX_WIDTH  16
#define GROUND_BUTTON_BBOX_HEIGHT 16

#define GROUND_BUTTON_PRESSED_BBOX_WIDTH  0
#define GROUND_BUTTON_PRESSED_BBOX_HEIGHT 0


#define GROUND_BUTTON_STATE_NORMAL		0
#define GROUND_BUTTON_STATE_PRESSED		1

#define GROUND_BUTTON_ANI_NORMAL		13001
#define GROUND_BUTTON_ANI_PRESSED		13002

#define GROUND_BUTTON_PRESSED_OFFSET_Y 6

class CGroundButton : public CGameObject
{
	bool pressed;
public:
	CGroundButton(float x, float y) : CGameObject(x, y) {
		this->SetState(GROUND_BUTTON_STATE_NORMAL);
		pressed = false;
	};
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state) { 
		switch (state)
		{
			case GROUND_BUTTON_STATE_NORMAL:
				pressed = false;
				break;
			case GROUND_BUTTON_STATE_PRESSED:
				pressed = true;
				y+= GROUND_BUTTON_PRESSED_OFFSET_Y;
				break;
		}
		this ->state = state;

	}
	void SetPressed(bool pressed) { this->pressed = pressed; }
	bool GetPressed() { return pressed; }

	int GetObjectType () { return OBJECT_TYPE_GROUND_BUTTON; }
};