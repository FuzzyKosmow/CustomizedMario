#include "BigColorBrick.h"
#include "Mario.h"
#include "Textures.h"
#include "Turtle.h"
#include "Goomba.h"
void CBigColorBrick::Render()
{
	if (height <= 0) return;
	if (width <= 0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	
	
	for (int i = 0; i < height; i++) //Go through each row
	{
		xx = x;
		for (int j = 0; j < width; j++) //Draw horizontally
		{
			if (i == 0) //Top row
			{
				if (j == 0) //Draw the first one
				{
					s->Get(this->spriteIDBeginTop)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}
				else if (j == width - 1) //Draw the last one + shadow
				{
					s->Get(ID_SPRITE_COLOR_BRICK_SHADOW_VERTICAL_1)->Draw(xx + 10, yy + COLOR_BRICK_HEIGHT - 5);
					s->Get(this->spriteIDEndTop)->Draw(xx, yy);
					
					xx += COLOR_BRICK_WIDTH;
				}
				else //Draw the middle ones
				{
					s->Get(this->spriteIDMiddleTop)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}
			}
			else if (i == height - 1) // Last row 
			{
				if (j == 0) //Draw the first one
				{
					s->Get(this->spriteIDBeginBottom)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}
				else if (j == width - 1) //Draw the last one
				{
					s->Get(ID_SPRITE_COLOR_BRICK_SHADOW_VERTICAL_2)->Draw(xx + 10, yy + COLOR_BRICK_HEIGHT / 2);
					s->Get(this->spriteIDEndBottom)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}
				else //Draw the middle ones
				{
					
					s->Get(this->spriteIDMiddleBottom)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}
			}
			else //Middle rows
			{
				if (j == 0) //Draw the first one
				{
					s->Get(this->spriteIDBeginMiddle)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}
				else if (j ==width - 1) //Draw the last one
				{
					s->Get(ID_SPRITE_COLOR_BRICK_SHADOW_VERTICAL_2)->Draw(xx + 10, yy + COLOR_BRICK_HEIGHT / 2);
					s->Get(this->spriteIDEndMiddle)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}
				else //Draw the middle ones
				{
					s->Get(this->spriteIDMiddleMiddle)->Draw(xx, yy);
					xx += COLOR_BRICK_WIDTH;
				}

			}

		}
		yy += COLOR_BRICK_HEIGHT;

	}
	RenderBoundingBox();
}

void CBigColorBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//Render a straight line
	l = x - COLOR_BRICK_WIDTH/2;
	t = y - COLOR_BRICK_HEIGHT/2;
	r = x + COLOR_BRICK_WIDTH*(width-1)+ COLOR_BRICK_WIDTH/2;
	b = y - COLOR_BRICK_HEIGHT/2;

}





void CBigColorBrick::RenderBoundingBox()
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

	float xx = x - COLOR_BRICK_WIDTH / 2 + rect.right / 2;
	float yy = y - COLOR_BRICK_HEIGHT / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}


void CBigColorBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj) || dynamic_cast<CGoomba*>(e->obj) || dynamic_cast<CTurtle*>(e->obj) )
	{
		if (e->ny < 0)
		{
			blocking = false;
		}
	}
}
void CBigColorBrick::OnNoCollision(DWORD dt)
{
	blocking = true;
}

void CBigColorBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}