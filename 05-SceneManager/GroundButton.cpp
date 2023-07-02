#include "GroundButton.h"


void CGroundButton::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	if (state == GROUND_BUTTON_STATE_NORMAL)
	{
		ani->Get(GROUND_BUTTON_ANI_NORMAL)->Render(x, y);

	}
	else if (state == GROUND_BUTTON_STATE_PRESSED)
	{
		ani->Get(GROUND_BUTTON_ANI_PRESSED)->Render(x, y);
	}
	RenderBoundingBox();
}

void CGroundButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state ==  GROUND_BUTTON_STATE_NORMAL)
	{
		l = x - GROUND_BUTTON_BBOX_HEIGHT / 2;
		t = y - GROUND_BUTTON_BBOX_WIDTH / 2;
		r = x + GROUND_BUTTON_BBOX_HEIGHT / 2;
		b = y + GROUND_BUTTON_BBOX_WIDTH / 2;
	}
	else
	{
		l = x - GROUND_BUTTON_BBOX_HEIGHT / 2;
		t = y - GROUND_BUTTON_BBOX_WIDTH / 2;
		r = l;
		b = t;

	}
	
}

