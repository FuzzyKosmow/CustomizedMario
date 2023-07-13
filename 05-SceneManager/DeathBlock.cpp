#include "DeathBlock.h"
#include "Mario.h"
#include "Textures.h"

void DeathBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void DeathBlock::Render()
{
	RenderBoundingBox();
}

void DeathBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - customWidth / 2;
	t = y - customHeight / 2;
	r = l + customWidth;
	b = t + customHeight;
}


void DeathBlock::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (LONG)customWidth;
	rect.bottom = (LONG)customHeight;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}


DeathBlock::DeathBlock(float x, float y, float width, float height)  : CGameObject(x,y)
{
	this->customWidth = width;
	this->customHeight = height;
}


void DeathBlock::OnCollisionWith (LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		mario->SetState(MARIO_STATE_DIE);
	}

}