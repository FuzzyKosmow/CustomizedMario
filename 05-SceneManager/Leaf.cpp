#include "Leaf.h"


CLeaf::CLeaf(float x, float y, bool activate) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	activated = activate;
	SetState(LEAF_STATE_NOT_ACTIVATED);
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == LEAF_STATE_NOT_ACTIVATED)
	{
		//No hit box yet.
	}
	else if (state == LEAF_STATE_FLYING)
	{
		left = x - LEAF_BBOX_WIDTH / 2;
		top = y - LEAF_BBOX_HEIGHT / 2;
		right = left + LEAF_BBOX_WIDTH;
		bottom = top + LEAF_BBOX_HEIGHT;
	}


}

void CLeaf::Render()
{
	CSprites * s = CSprites::GetInstance();
	if (vx >= 0)
	{
		s->Get(ID_SPRITE_LEAF_RIGHT)->Draw(x, y);
	}
	else
	{
		s->Get(ID_SPRITE_LEAF_LEFT)->Draw(x, y);
	}
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	
	
	if (GetState() == LEAF_STATE_FLYING)
	{
		if (abs(vx) >= LEAF_MAX_VX)
		{
			flyTimeOutStart = GetTickCount64();
			vx = 0;
			ax *= -1;
			vy = LEAF_MAX_VY;
		}
		if (GetTickCount64() - flyTimeOutStart >= LEAF_FLY_TIME_OUT)
		{
			vx += ax * dt;
			vy = LEAF_MAX_VY / 2;
		}
	
		

	}

	//progress collision
	CCollision::GetInstance()->Process(this, dt, coObjects);
}




void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_NOT_ACTIVATED:
		vx = 0;
		vy = 0;
		break;
	case LEAF_STATE_FLYING:
		ax = LEAF_AX;
		vy = LEAF_MAX_VY;
		break;
	}
}