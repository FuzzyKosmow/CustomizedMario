#pragma once
#include "FlyingTurtle.h"





CFlyingTurtle::CFlyingTurtle(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FLYING_TURTLE_GRAVITY;
	die_start = -1;

	jump_count = FLYING_FLYING_TURTLE_JUMP_COUNT;
	SetState(FLYING_TURTLE_STATE_FLYING);
}


void CFlyingTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLYING_TURTLE_STATE_WALKING || state == FLYING_TURTLE_STATE_FLYING)
	{
		left = x - FLYING_TURTLE_BBOX_WIDTH / 2;
		top = y - FLYING_TURTLE_BBOX_HEIGHT / 2;
		right = left + FLYING_TURTLE_BBOX_WIDTH;
		bottom = top + FLYING_TURTLE_BBOX_HEIGHT;
	}
	else if (state == FLYING_TURTLE_STATE_SHELL || state == FLYING_TURTLE_STATE_SHELL_MOVING)
	{
		left = x - FLYING_TURTLE_SHELL_BBOX_WIDTH / 2;
		top = y - FLYING_TURTLE_SHELL_BBOX_HEIGHT / 2;
		right = left + FLYING_TURTLE_SHELL_BBOX_WIDTH;
		bottom = top + FLYING_TURTLE_SHELL_BBOX_HEIGHT;

	}
	else
	{
		left = x - FLYING_TURTLE_BBOX_WIDTH / 2;
		top = y - FLYING_TURTLE_BBOX_HEIGHT_DIE / 2;
		right = left + FLYING_TURTLE_BBOX_WIDTH;
		bottom = top + FLYING_TURTLE_BBOX_HEIGHT_DIE;
	}


}

void CFlyingTurtle::RenderBoundingBox()
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

	float xx = x - FLYING_TURTLE_BBOX_WIDTH / 2 + rect.right / 2;
	float yy = y - FLYING_TURTLE_BBOX_HEIGHT / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}


void CFlyingTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}


void CFlyingTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == FLYING_TURTLE_STATE_SHELL_MOVING)
	{
		if (dynamic_cast<CGoomba*> (e->obj))
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

			goomba->SetState(GOOMBA_STATE_DIE);


		}
		else if (dynamic_cast<CLootBrick*>(e->obj))
		{
			CLootBrick* lootBrick = dynamic_cast<CLootBrick*>(e->obj);

			if (lootBrick->GetCurrentState() == LOOT_BRICK_STATE_NOT_LOOTED)
			{

				lootBrick->ShowLoot();

			}
		}
		
	}
	
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFlyingTurtle*>(e->obj)) return;
	if (e->ny != 0)
	{
		isOnPlatform = true;
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}



}


void CFlyingTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += ay * dt;
	if (state == FLYING_TURTLE_STATE_FLYING)
	{
		vx += ax * dt;
		if (isOnPlatform)
		{
			if (!jump_series_started)
			{
				if (GetTickCount64() - jump_series_start > FLYING_FLYING_TURTLE_JUMP_SERIES_COOLDOWN)
				{
					jump_series_started = true;
					jump_series_start = GetTickCount64();
				}

			}
			else
			{
				if (GetTickCount64() - last_jump > FLYING_FLYING_TURTLE_TIME_BETWEEN_JUMP)
				{
					last_jump = GetTickCount64();

					if (jump_count != 1)
					{
						vy -= FLYING_TURTLE_JUMP_SPEED;
					}
					else //Last jump in the series
					{
						vy -= FLYING_TURTLE_JUMP_SPEED * 2;
					}

					jump_count--;

					if (jump_count == 0)
					{
						jump_series_started = false;
						jump_count = FLYING_FLYING_TURTLE_JUMP_COUNT;
					}
				}
			}
		}

	}
	else if (GetState() == FLYING_TURTLE_STATE_WALKING || state == FLYING_TURTLE_STATE_SHELL_MOVING)
	{
		vx += ax * dt;
	}
	else if (state == FLYING_TURTLE_STATE_DIE_BY_ATTACK && GetTickCount64() - die_start > FLYING_TURTLE_DIE_TIMEOUT)
	{
		isDeleted = true;
		return;
	}
	isOnPlatform = false;
	//progress collision
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlyingTurtle::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == FLYING_TURTLE_STATE_WALKING)
	{
		if (vx <= 0)
			animations->Get(ANI_ID_FLYING_TURTLE_WALKING_LEFT)->Render(x, y);
		else
			animations->Get(ANI_ID_FLYING_TURTLE_WALKING_RIGHT)->Render(x, y);
	}
	else if (state == FLYING_TURTLE_STATE_SHELL)
	{
		animations->Get(ANI_ID_FLYING_TURTLE_SHELL)->Render(x, y);
	}
	else if (state == FLYING_TURTLE_STATE_SHELL_MOVING)
	{
		animations->Get(ANI_ID_FLYING_TURTLE_SHELL_MOVING)->Render(x, y);
	}
	else if (state == FLYING_TURTLE_STATE_FLYING)
	{
		if (vx <=0)
			animations->Get(ANI_ID_FLYING_TURTLE_FLYING_LEFT)->Render(x, y);
		else
			animations->Get(ANI_ID_FLYING_TURTLE_FLYING_RIGHT)->Render(x, y);
	}
	else if (state == FLYING_TURTLE_STATE_DIE_BY_ATTACK)
	{
		animations->Get(ANI_ID_FLYING_TURTLE_SHELL)->Render(x, y,180);
	}
}


void CFlyingTurtle::SetState(int state)
{
	switch (state)
	{
	case FLYING_TURTLE_STATE_FLYING:
	{
		vx = FLYING_TURTLE_WALKING_SPEED;
		ay = FLYING_TURTLE_FLYING_GRAVITY;
		break;
	}
	
	case FLYING_TURTLE_STATE_WALKING:
	{
		vx = FLYING_TURTLE_WALKING_SPEED;
		ay = FLYING_TURTLE_GRAVITY;
		y-= JUMPED_ON_OFFSET;
		break;
	}

	case FLYING_TURTLE_STATE_SHELL:
	{
		ay = FLYING_TURTLE_GRAVITY;
		vx = 0;
		y -= JUMPED_ON_OFFSET;
		break;
	}
	case FLYING_TURTLE_STATE_SHELL_MOVING:
	{
		ay = FLYING_TURTLE_GRAVITY;
		vx = FLYING_TURTLE_SHELL_SPEED;
		y -= JUMPED_ON_OFFSET;
		break;
	}
	case FLYING_TURTLE_STATE_DIE_BY_ATTACK:
	{
		die_start = GetTickCount64();
		ay = FLYING_TURTLE_GRAVITY;
		vy = -FLYING_TURTLE_DIE_BY_ATTACK_DEFLECT_VX;
		if (vx >0)
			vx = FLYING_TURTLE_DIE_BY_ATTACK_DEFLECT_VX;
		else
			vx = -FLYING_TURTLE_DIE_BY_ATTACK_DEFLECT_VX;
	}
	}
	this->state = state;
}