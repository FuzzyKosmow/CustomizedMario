#include "MarioTailAttack.h"
#include "PlayScene.h"
#include "SecretBrickWithButton.h"
#include "FlyingGoomba.h"
#include "FlyingTurtle.h"
#include "Turtle.h"
#include "ShootingPlant.h"
#include "EatingPlant.h"
#include "HUD.h"
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


void CMarioTailAttack::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CSecretBrickWithButton*>(e->obj))
	{
		CSecretBrickWithButton* brick = dynamic_cast<CSecretBrickWithButton*>(e->obj);
		brick->Break();
	}
	else if (dynamic_cast<CBrick*>(e->obj))
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		brick->Break();
	}
}


void CMarioTailAttack::OnNoCollision(DWORD dt)
{
	//DebugOut(L"NO COLLISION\n");
	/*x+= vx * dt;
	y+= vy * dt;*/
	
}

void CMarioTailAttack::OnTriggerEnter(LPCOLLISIONEVENT e)
{
	/*DebugOut(L"Ontrigger function object type: %d\n", e->obj->GetObjectType());*/
	if (dynamic_cast<CSecretBrickWithButton*>(e->obj)) //Secret Brick
	{
		CSecretBrickWithButton* brick = dynamic_cast<CSecretBrickWithButton*>(e->obj);
		if (!brick->IsDeleted())
		{
			brick->Break(); //Already have built in score pop up
			
			
		}
		
	}
	else if (dynamic_cast<CBrick*>(e->obj)) //Brick
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		if (!brick->IsDeleted())
		{
			brick->Break();
			HUD:: GetInstance()->PopUpScoreAtMario(BRICK_BREAK_SCORE);
		}
		
	}
	else if (dynamic_cast<CLootBrick*>(e->obj))
	{
		CLootBrick* brick = dynamic_cast<CLootBrick*> (e->obj);
		
		brick->ShowLoot();
		
		
		
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		if (goomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
		{
			goomba->SetState(GOOMBA_STATE_DIE_BY_ATTACK);
			HUD::GetInstance()->PopUpScoreAtMario(SCORE_GOOMBA_KILL);
		}

		
		
	}
	else if (dynamic_cast<CFlyingGoomba*>(e->obj))
	{
		CFlyingGoomba* goomba = dynamic_cast<CFlyingGoomba*>(e->obj);
	
		if (goomba->GetState () != FLYING_GOOMBA_STATE_DIE_BY_ATTACK)
		{
			goomba->SetState(FLYING_GOOMBA_STATE_DIE_BY_ATTACK);
			HUD::GetInstance()->PopUpScoreAtMario(SCORE_GOOMBA_KILL);
		}
	}
	else if (dynamic_cast <CTurtle*>(e->obj))
	{
		CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
		if (turtle->GetState() != TURTLE_STATE_DIE_BY_ATTACK)
		{
			turtle->SetState(TURTLE_STATE_DIE_BY_ATTACK);
			HUD::GetInstance()->PopUpScoreAtMario(SCORE_TURTLE_KILL);

		}
		
	}
	else if (dynamic_cast<CFlyingTurtle*>(e->obj))
	{
		CFlyingTurtle* turtle = dynamic_cast<CFlyingTurtle*>(e->obj);
		if (turtle->GetState() != FLYING_TURTLE_STATE_DIE_BY_ATTACK)
		{
			turtle->SetState(FLYING_TURTLE_STATE_DIE_BY_ATTACK);
			HUD::GetInstance()->PopUpScoreAtMario(SCORE_TURTLE_KILL);
		}
		
	}
	else if (dynamic_cast<CShootingPlant*>(e->obj))
	{
		CShootingPlant* plant = dynamic_cast<CShootingPlant*>(e->obj);
		if (!plant->IsDeleted())
		{
			plant->Delete();
			HUD::GetInstance()->PopUpScoreAtMario(SHOOTING_PLANT_SCORE);
		}
		

	}
	//Eating plant
	else if (dynamic_cast<CEatingPlant*>(e->obj))
	{
		CEatingPlant* plant = dynamic_cast<CEatingPlant*>(e->obj);
		if (!plant->IsDeleted())
		{
		
			plant->Delete();
			HUD::GetInstance()->PopUpScoreAtMario(EATING_PLANT_SCORE);
		}

	}
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
		////Static collision handling here because it doesnt really change pos and kinda just suddenly appear.
		//// Act more like a scanner
		//float t, l, b, r;
		//GetBoundingBox(l, t, r, b);
		//for (size_t i = 0; i < coObjects->size(); i++)
		//{
		//	LPGAMEOBJECT obj = coObjects->at(i);
		//	float oX, oY;
		//	obj->GetPosition(oX, oY);
		//	if ((oX > l && oX < r) && (oY > t && oY < b))
		//	{
		//		if (dynamic_cast<CSecretBrickWithButton*>(obj))
		//		{
		//							CSecretBrickWithButton* brick = dynamic_cast<CSecretBrickWithButton*>(obj);
		//			brick->Break();
		//		}
		//		else
		//		if (dynamic_cast<CBrick*>(obj))
		//		{
		//			CBrick* brick = dynamic_cast<CBrick*>(obj);
		//			brick->Break();
		//		}
		//	}


		//}

	}

	CCollision::GetInstance ()->Process(this, dt, coObjects);
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
