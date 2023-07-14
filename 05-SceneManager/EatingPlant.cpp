#include "EatingPlant.h"


void CEatingPlant::Render()
{
	
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_PLANT_STRAIGHT_UP)->Render(x, y);
	
	
	/*RenderBoundingBox();*/
}

void CEatingPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{


	//If player go out of detection zone, reset . A way to hide things
	if (!dZone->PlayerDetected())
	{
		x = baseX;
		y = baseY;
		idle_start = 0;

		show_start = 0;
		retract_start = 0;
		state = EATING_PLANT_STATE_IDLE;
		return;
	}
	float mx, my;
	LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
	scene->GetPlayer()->GetPosition(mx, my);

	if (abs(mx - x) < EATING_PLANT_MIN_DISTANCE_TO_PLAYER && state == EATING_PLANT_STATE_IDLE)
	{
		x = baseX;
		y = baseY;
		idle_start = 0;
		
		show_start = 0;
		retract_start = 0;
		
		state = EATING_PLANT_STATE_IDLE;
		return;
	}

	if (state == EATING_PLANT_STATE_IDLE)
	{
		if (dZone->PlayerDetected() && GetTickCount64() - idle_start > EATING_PLANT_IDLE_TIME)
		{
			state = EATING_PLANT_STATE_SHOWING;
			show_start = GetTickCount64();
		}
		else
		{
			x = baseX;
			y = baseY;
		}


	}
	else if (state == EATING_PLANT_STATE_SHOWING)
	{
		if (GetTickCount64() - show_start > EATING_PLANT_SHOW_TIME)
		{
			state = EATING_PLANT_STATE_SHOWN;
			shown_start = GetTickCount64();
		}
		else
		{
			float heightAddEachFrame = (1000.0f / MAX_FRAME_RATE) * (EATING_PLANT_SHOW_HEIGHT_DIFFERENCE) / EATING_PLANT_SHOW_TIME;
			y -= heightAddEachFrame;
		}
	}
	else if (state == EATING_PLANT_STATE_SHOWN)
	{
		if (GetTickCount64() - shown_start > EATING_PLANT_SHOWN_TIME)
		{
			state = EATING_PLANT_STATE_RETRACT;
			retract_start = GetTickCount64();
		}
		
	}
	else if (state == EATING_PLANT_STATE_RETRACT)
	{
		if (GetTickCount64() - retract_start > EATING_PLANT_RETRACT_TIME)
		{
			x = baseX;
			y = baseY;
			x = baseX;
			y = baseY;

			shown_start = 0;
			show_start = 0;
			retract_start = 0;
		
			state = EATING_PLANT_STATE_IDLE;
			idle_start = GetTickCount64();
		}
		else
		{
			float heightAddEachFrame = (1000.0f / MAX_FRAME_RATE) * (EATING_PLANT_SHOW_HEIGHT_DIFFERENCE) / EATING_PLANT_RETRACT_TIME;
			y += heightAddEachFrame;
		}
	}
}

void CEatingPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - EATING_PLANT_BBOX_WIDTH / 2;
	top = y - EATING_PLANT_BBOX_HEIGHT / 2;
	right = x + EATING_PLANT_BBOX_WIDTH / 2;
	bottom = y + EATING_PLANT_BBOX_HEIGHT / 2;

}
void CEatingPlant::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - EATING_PLANT_BBOX_WIDTH / 2 + rect.right / 2;
	float yy = y - EATING_PLANT_BBOX_HEIGHT / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}