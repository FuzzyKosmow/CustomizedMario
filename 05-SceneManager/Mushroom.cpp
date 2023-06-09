#include "Mushroom.h"
#include "Goomba.h"
CShroom::CShroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = SHROOM_GRAVITY;

	SetState(SCHROOM_STATE_NOT_ACTIVATED);
}

void CShroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == SCHROOM_STATE_NOT_ACTIVATED)
	{
		//No hit box yet.
	}
	else if (state == SHROOM_STATE_WALKING)
	{
		left = x - SHROOM_BBOX_WIDTH / 2;
		top = y - SHROOM_BBOX_HEIGHT / 2;
		right = left + SHROOM_BBOX_WIDTH;
		bottom = top + SHROOM_BBOX_HEIGHT;
	}
	

}

void CShroom::Render()
{
	CAnimations * animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SHROOM_WALKING)->Render(x, y);
}

void CShroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	
	if (GetState() == SHROOM_STATE_WALKING)
	{
		vy += ay * dt;
		vx += ax * dt;
		
	}
	
	//progress collision
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CShroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CShroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CShroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SCHROOM_STATE_NOT_ACTIVATED:
		vx = 0;
		vy = 0;
		break;
	case SHROOM_STATE_WALKING:
		vx = -SHROOM_WALKING_SPEED;
		vy = 0;
		break;
	}
}