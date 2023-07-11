#include "OverworldMario.h"

void COverworldMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Move mario. Check if mario has moved enough distance, if enough, stop.
	if (isMoving)
	{
		
		if (travelledDistance >= OVERWORLD_MARIO_TRAVEL_DISTANCE_BETWEEN_NODE)
		{
			isMoving = false;
			travelledDistance = 0;
			vx = 0;
			vy = 0;
		}
		else
		{
			vy += ay * dt;
			vx += ax * dt;
			travelledDistance += sqrt(vx * vx + vy * vy) * dt;
		}

	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
	/*DebugOutTitle(L"Pos: %f %f", x, y);*/
	DebugOutTitle(L"Is on node: %d", isOnNode);
}


void COverworldMario::Render()
{
	CAnimations * animations = CAnimations::GetInstance();

	animations->Get(ANI_ID_OVERWORLD_MARIO_SMALL)->Render(x, y);
	RenderBoundingBox();
}

void COverworldMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//Stop if hit object blocking from any direction
	if ((e->ny != 0 || e->nx != 0) && e->obj->IsBlocking())
	{
		isMoving = false;
		travelledDistance = 0;
		vx = 0;
		vy = 0;
	}
}

int COverworldMario::Move(OverworldMovementDirection direction)
{
	if (isMoving)
		return 0;
	switch (direction)
	{
	case OverworldMovementDirection_Left:
		vx = -OVERWORLD_MARIO_TRAVEL_SPEED;
		vy = 0;
		break;
	case OverworldMovementDirection_Right:
		 vx = OVERWORLD_MARIO_TRAVEL_SPEED;
		 vy = 0;
	
		break;
	case OverworldMovementDirection_Up:
		vx = 0;
		vy = -OVERWORLD_MARIO_TRAVEL_SPEED;
	
		break;
	case OverworldMovementDirection_Down:
		vx = 0;
		vy = OVERWORLD_MARIO_TRAVEL_SPEED;
		break;
	default:
		break;
	}
	isMoving = true;
	
		return 1;
}