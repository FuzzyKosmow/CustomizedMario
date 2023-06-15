#include "Turtle.h"


CTurtle::CTurtle(float x, float y, float limitLeft, float limitRight) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = TURTLE_GRAVITY;
	die_start = -1;
	this->litmitLeft = limitLeft;
	this->litmitRight = limitRight;
	SetState(TURTLE_STATE_WALKING);
}


void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TURTLE_STATE_WALKING)
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT;
	}
	else if (state == TURTLE_STATE_SHELL || state == TURTLE_STATE_SHELL_MOVING)
	{
		left = x - TURTLE_SHELL_BBOX_WIDTH / 2;
		top = y - TURTLE_SHELL_BBOX_HEIGHT / 2;
		right = left + TURTLE_SHELL_BBOX_WIDTH;
		bottom = top + TURTLE_SHELL_BBOX_HEIGHT;

	}
	else
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT_DIE / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT_DIE;
	}


}

void CTurtle::RenderBoundingBox()
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

	float xx = x - TURTLE_BBOX_WIDTH / 2 + rect.right / 2;
	float yy = y - TURTLE_BBOX_HEIGHT / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}


void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}


void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == TURTLE_STATE_SHELL_MOVING)
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
	if (dynamic_cast<CTurtle*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (state == TURTLE_STATE_WALKING || state == TURTLE_STATE_SHELL_MOVING)
	{
		if (dynamic_cast<CMario*>(e->obj))
		{
			if (e->nx > 0 || e->nx < 0)
			{
				CMario* mario = dynamic_cast<CMario*>(e->obj);
				mario->TakeDamage();
			}
			
		}
		if (state == TURTLE_STATE_SHELL_MOVING)
		{
			if (dynamic_cast<CGoomba*> (e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				
					goomba->SetState(GOOMBA_STATE_DIE);
			
				
			}
			else if (dynamic_cast<CLootBrick*>(e->obj))
			{
				//Nothing yet
			}
		}

	}


}


void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (GetState() == TURTLE_STATE_WALKING || state == TURTLE_STATE_SHELL_MOVING)
	{
		vy += ay * dt;
		vx += ax * dt;
		if (state == TURTLE_STATE_WALKING)
		{
			if (x > litmitRight)
			{
				x = litmitRight;
				vx = -vx;
			}
			if (x < litmitLeft)
			{
				x = litmitLeft;
				vx = -vx;
			}
		}
		
	}

	//progress collision
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTurtle::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == TURTLE_STATE_WALKING)
	{
		if (vx <= 0)
			animations->Get(ANI_ID_TURLTE_WALKING_LEFT)->Render(x, y);
		else
			animations->Get(ANI_ID_TURLTE_WALKING_RIGHT)->Render(x, y);
	}
	else if (state == TURTLE_STATE_SHELL)
	{
		animations->Get(ANI_ID_TURLTE_SHELL)->Render(x, y);
	}
	else if (state == TURTLE_STATE_SHELL_MOVING)
	{
		animations->Get(ANI_ID_TURLTE_SHELL_MOVING)->Render(x, y);
	}
}


void CTurtle::SetState(int state)
{
	switch (state)

	{
	case TURTLE_STATE_WALKING:
	{
		vx = TURTLE_WALKING_SPEED;
		
		break;
	}

	case TURTLE_STATE_SHELL:
	{
		vx = 0;
		
		break;
	}
	case TURTLE_STATE_SHELL_MOVING:
	{
		vx = TURTLE_SHELL_SPEED;
		
		y -= JUMPED_ON_OFFSET;
		break;
	}

	}
	this->state = state;
}