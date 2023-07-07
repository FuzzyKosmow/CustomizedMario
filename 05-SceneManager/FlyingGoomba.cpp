#include "FlyingGoomba.h"
#include "Mario.h"
#include "Animation.h"
CFlyingGoomba::CFlyingGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	jump_count = FLYING_GOOMBA_JUMP_COUNT;
	die_start = -1;
	SetState(FLYING_GOOMBA_STATE_FLYING);
}

void CFlyingGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLYING_GOOMBA_STATE_DIE)
	{
		left = x - FLYING_GOOMBA_BBOX_WIDTH / 2;
		top = y - FLYING_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + FLYING_GOOMBA_BBOX_WIDTH;
		bottom = top + FLYING_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - FLYING_GOOMBA_BBOX_WIDTH / 2;
		top = y - FLYING_GOOMBA_BBOX_HEIGHT / 2;
		right = left + FLYING_GOOMBA_BBOX_WIDTH;
		bottom = top + FLYING_GOOMBA_BBOX_HEIGHT;
	}
}

void CFlyingGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFlyingGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking() ) return;
	if (dynamic_cast<CFlyingGoomba*>(e->obj)) return;
	if (e->ny != 0 && e->obj->IsBlocking())
	{

		vy = 0;
		isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = -vx;
		}

}

void CFlyingGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	
	//Do 2 light jump then one big jump. Before walking a bit then resume back to the jump series. Last jump is heavy jump
	if (state == FLYING_GOOMBA_STATE_FLYING)
	{
		if (isOnPlatform)
		{
			if (!jump_series_started)
			{
				if (GetTickCount64() - jump_series_start > FLYING_GOOMBA_JUMP_SERIES_COOLDOWN)
				{
					jump_series_started = true;
					jump_series_start = GetTickCount64();
				}

			}
			else
			{
				if (GetTickCount64() - last_jump > FLYING_GOOMBA_TIME_BETWEEN_JUMP)
				{
					last_jump = GetTickCount64();

					if (jump_count != 1)
					{
						vy -= FLYING_GOOMBA_JUMP_SPEED;
					}
					else
					{
						vy -= FLYING_GOOMBA_JUMP_SPEED * 2;
					}

					jump_count--;

					if (jump_count == 0)
					{
						jump_series_started = false;
						jump_count = FLYING_GOOMBA_JUMP_COUNT;
					}
				}
			}
		}
		
	}

	if ((state == FLYING_GOOMBA_STATE_DIE || state == FLYING_GOOMBA_STATE_DIE_BY_ATTACK) && (GetTickCount64() - die_start > FLYING_GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	vy += ay * dt;
	vx += ax * dt;
	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlyingGoomba::Render()
{
	
	int rotation = 0;
	int aniId = -1;
	if (state == FLYING_GOOMBA_STATE_DIE )
	{
		aniId = ID_ANI_FLYING_GOOMBA_DIE;
		
	}
	else if (state == FLYING_GOOMBA_STATE_DIE_BY_ATTACK)
	{

		aniId = ID_ANI_FLYING_GOOMBA_WALKING;
		rotation = 180;
		
	}
	else if (state == FLYING_GOOMBA_STATE_WALKING)
	{
		aniId = ID_ANI_FLYING_GOOMBA_WALKING;
	}
	else if (state == FLYING_GOOMBA_STATE_FLYING)
	{
		aniId = ID_ANI_FLYING_GOOMBA_FLYING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, (float)rotation);
	RenderBoundingBox();
}

void CFlyingGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLYING_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (FLYING_GOOMBA_BBOX_HEIGHT - FLYING_GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case FLYING_GOOMBA_STATE_DIE_BY_ATTACK:
		die_start = GetTickCount64();
		ay = FLYING_GOOMBA_WALKING_GRAVITY;
		vy -= FLYING_GOOMBA_DIE_BY_ATTACK_VY_DEFLECT;
		if (vx > 0)
			vx = FLYING_GOOMBA_DIE_BY_ATTACK_VX_DEFLECT;
		else
			vx = -FLYING_GOOMBA_DIE_BY_ATTACK_VX_DEFLECT;
		break;
	case FLYING_GOOMBA_STATE_WALKING:
		vx = -FLYING_GOOMBA_WALKING_SPEED;
		ay = FLYING_GOOMBA_WALKING_GRAVITY;
		y -= (FLYING_GOOMBA_BBOX_HEIGHT - FLYING_GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vy = 0;
		break;
	case FLYING_GOOMBA_STATE_FLYING:
		ay = FLYING_GOOMBA_FLYING_GRAVITY;
		
		vx = -FLYING_GOOMBA_WALKING_SPEED;
		break;
	
	}
}

