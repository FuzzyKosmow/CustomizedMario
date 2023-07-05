#include "MarioTailAttack.h"
#include "PlayScene.h"
#include "SecretBrickWithButton.h"
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//														//////////
//														//////////
//				MARIO RACCOON ATTACK SECTION			//////////
//														//////////
// 														//////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void CMarioTailAttack::Render()
{
	RenderBoundingBox();
}


CMarioTailAttack::CMarioTailAttack(float x, float y) : CGameObject(x, y)
{
	isActive = false;
	direction = 0;
	player = NULL;
}





void CMarioTailAttack::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (isActive)
	{
		left = x - MARIO_BIG_BBOX_WIDTH / 2;
		top = y - MARIO_BIG_BBOX_HEIGHT / 2;
		right = x + MARIO_BIG_BBOX_WIDTH / 2;
		bottom = y + MARIO_BIG_BBOX_HEIGHT / 2;
	}



}

void CMarioTailAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (isActive)
	{
		if (GetTickCount64() - raccoonAttackStart > MARIO_RACCOON_ATTACK_TIME)
		{
			isActive = false;
			raccoonAttackStart = 0;
		};
		//Static collision handling here because it doesnt really change pos and kinda just suddenly appear.
		// Act more like a scanner
		float t, l, b, r;
		GetBoundingBox(l, t, r, b);
		for (size_t i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			float oX, oY;
			obj->GetPosition(oX, oY);
			if ((oX > l && oX < r) && (oY > t && oY < b))
			{
				if (dynamic_cast<CSecretBrickWithButton*>(obj))
				{
									CSecretBrickWithButton* brick = dynamic_cast<CSecretBrickWithButton*>(obj);
					brick->Break();
				}
				else
				if (dynamic_cast<CBrick*>(obj))
				{
					CBrick* brick = dynamic_cast<CBrick*>(obj);
					brick->Break();
				}
			}


		}

	}


}

void CMarioTailAttack::Attack(int dir)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	player = scene->GetPlayer();

	player->GetPosition(x, y);
	isActive = true;

	if (dir > 0)
	{
		nx = 1;
		raccoonAttackStart = GetTickCount64();
		x += MARIO_BIG_BBOX_WIDTH;
	}
	else
	{
		nx = -1;
		raccoonAttackStart = GetTickCount64();
		x -= MARIO_BIG_BBOX_WIDTH;
	}


}
