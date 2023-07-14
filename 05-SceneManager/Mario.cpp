
#include "Mario.h"
#include "Detection.h"
#include "SecretBrickWithButton.h"
#include "Game.h"
#include "Brick.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "LootBrick.h"
#include "Collision.h"
#include "Mushroom.h"
#include "BigColorBrick.h"
#include "PlayScene.h"
#include "ShootingPlant.h"
#include "Turtle.h"
#include "Leaf.h"
#include "EatingPlant.h"
#include "FlyingGoomba.h"
#include "FlyingTurtle.h"
#include "ParticleSystem.h"
#include "SecretBrickWithButton.h"
#include "MarioTailAttack.h"
#include <algorithm>
#include "debug.h"
#include "Dimscreen.h"
#include "EndLevelLoot.h"
#include "Greenshroom.h"
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//														//////////
//														//////////
//				MARIO GENERAL SECTION					//////////
//														//////////
// 														//////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


CMario::CMario (float x, float y) : CGameObject(x, y)
{
	isSitting = false;
	maxVx = 0.0f;
	ax = 0.0f;
	ay = MARIO_GRAVITY;

	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	untouchable_start = -1;
	isOnPlatform = false;
	coin = 0;
	raccoonAttack_start = -1;

	//Get stats from Game
	CGame::GetInstance()->GetMarioStats(lives, score, coin);

	LPPLAYSCENE scene = (LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene();
	
	tailAttack = new CMarioTailAttack(x, y);
	scene->AddObject (tailAttack);
}


void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	/*DebugOutTitle(L"mario pos %f %f | cam pos   %f %f\n", x, y, camX, camY);*/
	DebugOutTitle(L"Drop distance %f\n", dropDistance);
	/*DebugOutTitle(L"Dead started at %d\n", dead_start)*/;
	//Go back to overworld if dead
	//DebugOutTitle(L"State %d\n", state);
	
	
	CGame::GetInstance()->UpdateMarioStats(lives, score, coin);
	//Handler ending after getting the loot
	if (sceneSwitchActivated)
		return;

	if (state == MARIO_ENDING_MOVE_RIGHT)
	{
		if (GetTickCount64() - end_level_walk_start > MARIO_WALK_TIME_BEFORE_DIME && !endLevelDimmed)
		{
			CDimScreenEffect::GetInstance()->MakeDimFor(MARIO_DIM_TIME, MARIO_DELAY_TIME,  MARIO_UNDIM_TIME);
			endLevelDimmed = true;
			dim_start = GetTickCount64();
		}
		if ((GetTickCount64() - dim_start > MARIO_DIM_TIME + MARIO_DIM_TIME )&& endLevelDimmed && !sceneSwitchActivated)
		{
			CGame::GetInstance()->InitiateSwitchScene(SCENE_ID_OVERWORLD);
			sceneSwitchActivated = true;
			return;
		}
		vx = MARIO_WALKING_SPEED;
		vy += ay * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);

		return;
	}
	if (state == MARIO_STATE_DIE)
	{
		if (GetTickCount64() - dead_start >= MARIO_DIE_TIME && !deadDimmed)
		{
			CDimScreenEffect::GetInstance()->MakeDimFor(MARIO_DIM_TIME, MARIO_DELAY_TIME, 0);
			deadDimmed = true;
		}
		else if (GetTickCount64() - dead_start >= MARIO_DIE_TIME + MARIO_DELAY_TIME+ MARIO_DIM_TIME)
		{
			CGame::GetInstance()->InitiateSwitchScene(SCENE_ID_OVERWORLD);
		}
		
	}




	LPPLAYSCENE scene = (LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene();
	if (scene->ControlIsLocked())
	{
		
		return;
	}
	
	//Handle the set colliable by time
	if (GetTickCount64() - uncolliableStart >= uncolliableTime && hasJustSetUncolliable)
	{
		colliable = true;
		hasJustSetUncolliable = false;
		uncolliableStart = 0;
		uncolliableTime = 0;


	}
	//Control the holding object here
	if (holdingObject)
	{
		LPGAME game = CGame::GetInstance();
		if (game->IsKeyDown(DIK_A) && !isSitting)
		{
			if (nx == 1)
			{
				holdObject->SetPosition(x + MARIO_BIG_BBOX_WIDTH, y);

			}
			else

			{
				holdObject->SetPosition(x - MARIO_BIG_BBOX_WIDTH, y);
			}
		}
		else
		{
			//Release object if not holding A
			if (dynamic_cast<CTurtle*> (holdObject))
			{
				CTurtle* turtle = dynamic_cast<CTurtle*> (holdObject);
				turtle->SetState(TURTLE_STATE_SHELL_MOVING);
				if (nx == 1)
				{
					//Nothing, default direction is on the right
				}
				else

				{
					float turtleVx = 0, turtlVy = 0;
					turtle->GetSpeed(vx, vy);
					turtle->SetSpeed(vx * -1, vy);
				}

			}
			else if (dynamic_cast<CFlyingTurtle*>(holdObject))
			{
				CFlyingTurtle * turtle = dynamic_cast<CFlyingTurtle*>(holdObject);
				turtle->SetState(FLYING_TURTLE_STATE_SHELL_MOVING);
				if (nx == 1)
				{
					//Nothing, default direction is on the right
				}
				else

				{
					float turtleVx = 0, turtlVy = 0;
					turtle->GetSpeed(vx, vy);
					turtle->SetSpeed(vx * -1, vy);
				}
			}
			holdingObject = false;
			holdObject = nullptr;
		}


	}
	//Handling mario raccoon flying gravity
	/*DebugOutTitle(L"Gravity: %f  flying: %d : %f\n", ay, isFlying,vy);
	DebugOut(L"Descend: %d\n", isDescending);*/
	vy += ay * dt;
	vx += ax * dt;
	//Make sure it's abs value is not pass MARIO_RACCOON_MAX_VY
	
	//Max speed limit
	if (abs(vy) > abs(MARIO_MAX_DROP_SPEED))
	{
		if (vy > 0)
			vy = MARIO_MAX_DROP_SPEED;
	}

	if (abs(vx) > abs(maxVx))
	{
		vx = maxVx;
		if (maxVx == MARIO_RUNNING_SPEED)
			maxSpeedReached = true;
	}
	else
	{
		maxSpeedReached = false;
	}

	if (GetTickCount64() - lastJumpPressed > MARIO_RACCOON_JUMP_INVERVAL_REQUIRED)
	{
		ay = MARIO_GRAVITY;
		vyFlyMax = MARIO_RACCOON_MAX_FLY_VY_PHASE_1;
		
	}
	else
	{
		if (level == MARIO_LEVEL_RACCOON)
		{
			if (maxSpeedReached && !isOnPlatform && isFlying) //Meaning it's flying
			{
				if (abs(vy) > abs(vyFlyMax))
				{
					if (vy > 0)
					{
						vy = vyFlyMax;
					}
					else
					{
						vy = -vyFlyMax;
					}
				}
				
				
			}
			else if (isDescending)
			{
				//Descend
				isFlying = false;
				//Make sure its not bigger than MARIO_RACCOON_DESCEND_MAX_DROP_VY
				if (abs(vy) > abs(MARIO_RACCOON_DESCEND_MAX_DROP_VY))
				{
					if (vy > 0)
					{
						vy = MARIO_RACCOON_DESCEND_MAX_DROP_VY;
					}
					else
					{
						vy = -MARIO_RACCOON_DESCEND_MAX_DROP_VY;
					}
				}


			}
		}
	}

	if (!isFlying) //Since only raccoon can fly
	{
		ay = MARIO_GRAVITY;
		flyTookOff = false;
	}


	//Handling speed
	
	


	if (isOnPlatform)
	{
		isFlying = false;
		ay = MARIO_GRAVITY;
		flyTookOff = false;
		isFlying = false;
		isDescending = false;
	}
	

	//Reset attack timer for raccoon attack
	if (isRaccoonAttacking)
	{
		if (GetTickCount64() - raccoonAttack_start > MARIO_RACCOON_ATTACK_TIME)
		{
			raccoonAttack_start = 0;
			isRaccoonAttacking = false;
			SetState(MARIO_STATE_IDLE);
			
		}

	}
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	
	
	isOnPlatform = false;
	
		
	CCollision::GetInstance()->Process(this, dt, coObjects);
	
}


//Collision section
void CMario::OnNoCollision(DWORD dt)
{

	x += vx * dt;
	y += vy * dt;
	if (!isOnPlatform && vy > 0)
	{
		dropDistance += vy * dt;
	}
	else
	{
		dropDistance = 0;
	}
	/*detector->SetPosition(x, y);*/
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<PlantProjectile*>(e->obj))
		OnCollisionWithPlantBullet(e);

	if (e->ny != 0 && e->obj->IsBlocking())
	{

		vy = 0;
		isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}


	if (dynamic_cast<CLootBrick*>(e->obj))
		OnCollisionWithLootBrick(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CShroom*>(e->obj))
		OnCollisionWithSchroom(e);
	else if (dynamic_cast<CShootingPlant*> (e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CTurtle*> (e->obj))
		OnCollisionWithTurtle(e);
	else if (dynamic_cast<CLeaf*> (e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CEatingPlant*> (e->obj))
		OnCollisionWithEatingPlant(e);
	else if (dynamic_cast<CFlyingGoomba*>(e->obj))
		OnCollisionWithFlyingGoomba(e);
	else if (dynamic_cast<CFlyingTurtle*>	(e->obj))
		OnCollisionWithFlyingTurtle(e);
	else if (dynamic_cast<CGroundButton*> (e->obj))
		OnCollisionWithGroundButton(e);
	else if (dynamic_cast<EndLevelLoot*>(e->obj))
		OnCollisionWithEndLevelLoot (e);

}
void CMario::AddScoreWithPopUp(int num)
{
	HUD::GetInstance()->PopUpScoreAtMario(num);
}
void CMario::OnCollisionWithEndLevelLoot (LPCOLLISIONEVENT e)
{
	
	e->obj->Delete();
	AddScoreWithPopUp(END_LEVEL_LOOT_GENERAL_SCORE);
	this->SetState(MARIO_ENDING_MOVE_RIGHT);

}

void CMario::OnCollisionWithFlyingTurtle(LPCOLLISIONEVENT e)
{
	CFlyingTurtle* turtle = dynamic_cast<CFlyingTurtle*>(e->obj);
	LPGAME game = CGame::GetInstance();
	if (e->ny < 0)
	{
		if (isFlying) return;
		if (turtle->GetState() == FLYING_TURTLE_STATE_FLYING ||
			turtle->GetState() == FLYING_TURTLE_STATE_WALKING)
		{
			if (turtle->GetState() == FLYING_TURTLE_STATE_FLYING)
			{
				turtle->SetState(FLYING_TURTLE_STATE_WALKING);
			}
			else
			{
				turtle->SetState(FLYING_TURTLE_STATE_SHELL);
			}

			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (turtle->GetState() == FLYING_TURTLE_STATE_SHELL)
		{
			turtle->SetState(FLYING_TURTLE_STATE_SHELL_MOVING);
			if (e->nx > 0)
			{
				turtle->SetSpeed(FLYING_TURTLE_SHELL_SPEED, 0);
			}
			else
			{
				turtle->SetSpeed(-FLYING_TURTLE_SHELL_SPEED, 0);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (turtle->GetState() == FLYING_TURTLE_STATE_SHELL_MOVING)
		{
			turtle->SetState(FLYING_TURTLE_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		AddScoreWithPopUp(SCORE_JUMP_ON);
	}
	else if (e->nx != 0 && turtle->GetState() == FLYING_TURTLE_STATE_SHELL && //Holding
		game->IsKeyDown(DIK_A)
		)
	{
		if (!holdingObject)
		{
			holdingObject = true;
			holdObject = turtle;
		}


	} 
	 else if (e->obj->GetState() == FLYING_TURTLE_STATE_WALKING //Hit by turtle
		|| e->obj->GetState() == FLYING_TURTLE_STATE_FLYING
		 || e->obj->GetState() == FLYING_TURTLE_STATE_SHELL_MOVING)
	{

			if (e->nx != 0 && !untouchable)
			{
				TakeDamage();
			}

		
	}
}

void CMario::OnCollisionWithFlyingGoomba(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		if (isFlying) return;
		if (e->obj->GetState() == FLYING_GOOMBA_STATE_FLYING)
		{
			e->obj->SetState(FLYING_GOOMBA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			AddScoreWithPopUp(SCORE_JUMP_ON*3);
		}
		else if (e->obj->GetState() == FLYING_GOOMBA_STATE_WALKING)
		{
			e->obj->SetState(FLYING_GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			AddScoreWithPopUp(SCORE_JUMP_ON);

		}


	}
	else if (e->obj->GetState() != FLYING_GOOMBA_STATE_DIE || e->obj->GetState() != FLYING_GOOMBA_STATE_DIE_BY_ATTACK)
	{
		if (!untouchable )
			TakeDamage();
	}
	
}

void CMario::OnCollisionWithEatingPlant(LPCOLLISIONEVENT e)
{
	TakeDamage();
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{

	SetLevel(MARIO_LEVEL_RACCOON);
	AddScoreWithPopUp(SCORE_LEAF);
	e->obj->Delete();
}

void CMario::OnCollisionWithGroundButton(LPCOLLISIONEVENT e)
{

	if (e->ny < 0)
	{
		if (e->obj->GetState() == GROUND_BUTTON_STATE_NORMAL)
		{
			e->obj->SetState(GROUND_BUTTON_STATE_PRESSED);
			AddScoreWithPopUp(GROUND_BUTTON_PRESS_SCORE);
		}
	}
}

void CMario::OnCollisionWithTurtle(LPCOLLISIONEVENT e)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
	LPGAME game = CGame::GetInstance();
	if (e->ny < 0)
	{
		if (isFlying) return;
		if (turtle->GetState() == TURTLE_STATE_WALKING)
		{
			turtle->SetState(TURTLE_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			
		}
		else if (turtle->GetState() == TURTLE_STATE_SHELL)
		{
			turtle->SetState(TURTLE_STATE_SHELL_MOVING);
			if (e->nx > 0)
			{
				turtle->SetSpeed(TURTLE_SHELL_SPEED, 0);
			}
			else
			{
				turtle->SetSpeed(-TURTLE_SHELL_SPEED, 0);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		
		}
		else if (turtle->GetState() == TURTLE_STATE_SHELL_MOVING)
		{
			turtle->SetState(TURTLE_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			
		}
		AddScoreWithPopUp(SCORE_JUMP_ON);
		
	}
	else if (e->nx != 0 && turtle->GetState() == TURTLE_STATE_SHELL &&
		game->IsKeyDown(DIK_A)
		)
	{
		if (!holdingObject)
		{
			holdingObject = true;
			holdObject = turtle;
		}


	}
	else //Hit by turtle
	{
		if (e->obj->GetState() == TURTLE_STATE_SHELL_MOVING)
		{
			if (e->nx != 0 && !untouchable)
			{
				TakeDamage();
			}
		}
		else if (e->obj->GetState() == TURTLE_STATE_WALKING)
		{
			
			if (e->nx != 0 && !untouchable)
			{
				TakeDamage();
			}

		

		}
	}

}
void CMario::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();

		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}

void CMario::OnCollisionWithPlantBullet(LPCOLLISIONEVENT e)
{
	if (!untouchable)
	{
		TakeDamage();
		e->obj->Delete();
	}

}



void CMario::OnCollisionWithSchroom(LPCOLLISIONEVENT e)
{
	if (state == MARIO_STATE_DIE) return;
	if (dynamic_cast<CGreenshroom*>(e->obj)) // 1 UP 
	{
		AddScoreWithPopUp(SCORE_GREENSHROOM);
		lives++;
		e->obj->Delete();
		return;
	}
	//Red schroom normal
	if ((GetLevel() == MARIO_LEVEL_SMALL || GetLevel() == MARIO_LEVEL_BIG) && dynamic_cast<CShroom*>(e->obj)->GetState() == SHROOM_STATE_WALKING)
	{
		SetLevel(MARIO_LEVEL_BIG);
		AddScoreWithPopUp(SCORE_MUSHROOM);
		e->obj->Delete();
	}
	else if (level == MARIO_LEVEL_RACCOON && dynamic_cast<CShroom*>(e->obj)->GetState() == SHROOM_STATE_WALKING)
	{
		SetLevel(MARIO_LEVEL_RACCOON);
		AddScoreWithPopUp(SCORE_MUSHROOM);
		e->obj->Delete();
	}

}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CSecretBrickWithButton*>(e->obj))
	{
		if (e->ny > 0) {
			CSecretBrickWithButton* brick = dynamic_cast<CSecretBrickWithButton*>(e->obj);
			brick->Break();
			
		}

	}
	else // Handle normal brick
		if (e->ny > 0)
		{
			CBrick* brick = dynamic_cast<CBrick*>(e->obj);
			brick->Break();
			
			AddScoreWithPopUp(BRICK_BREAK_SCORE);
		}
}

void CMario::OnCollisionWithLootBrick(LPCOLLISIONEVENT e)
{
	CLootBrick* lootBrick = dynamic_cast<CLootBrick*>(e->obj);
	//If mario hit it from below, set it to looted state

	if (e->ny > 0)
	{

		if (lootBrick->GetCurrentState() == LOOT_BRICK_STATE_NOT_LOOTED)
		{

			lootBrick->ShowLoot();
	
			
		}

	}

}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (isFlying) return;
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			AddScoreWithPopUp(SCORE_JUMP_ON);
		}
	}
	else // hit by Goomba
	{
		/*if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}*/
		if (!untouchable)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE || goomba->GetState() != GOOMBA_STATE_DIE_BY_ATTACK)
			{
				TakeDamage();
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
	AddScoreWithPopUp(SCORE_COIN);

}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;

	if (!isOnPlatform)
	{
		if (nx >= 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
		}
		else
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (nx > 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
		}
		else
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
		}
	}
	else if (vx > 0)
	{
		if (ax < 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
		}
		else if (ax == MARIO_ACCEL_RUN_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
		}
		else if (ax == MARIO_ACCEL_WALK_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
		}
	}
	else // vx < 0
	{
		if (ax > 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
		}
		else if (ax == -MARIO_ACCEL_RUN_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
		}
		else if (ax == -MARIO_ACCEL_WALK_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
		}
	}
	if (state == MARIO_ENDING_MOVE_RIGHT) aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (state == MARIO_STATE_FACING_FRONT)
	{
		return 403;
	}
	else
	if (!isOnPlatform)
	{
		if (nx >= 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;

		}

		else
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT_GRABBING;
			}
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{

				if (nx > 0)
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIO_IDLE_RIGHT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_IDLE_RIGHT;
				}
				else
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIO_IDLE_LEFT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_IDLE_LEFT;
				}

			}
			else if (vx > 0)
			{
				if (ax < 0)
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIO_IDLE_LEFT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
				}

				else if (ax == MARIO_ACCEL_RUN_X)
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIOR_RUNNING_RIGHT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				}

				else if (ax == MARIO_ACCEL_WALK_X)
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIO_WALKING_RIGHT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}

			}
			else // vx < 0
			{
				if (ax > 0)
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIO_IDLE_RIGHT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_BRACE_LEFT;
				}

				else if (ax == -MARIO_ACCEL_RUN_X)
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIOR_RUNNING_LEFT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
				{
					if (holdingObject)
					{
						aniId = ID_ANI_MARIO_WALKING_LEFT_GRABBING;
					}
					else
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}

			}

			if (state == MARIO_ENDING_MOVE_RIGHT) aniId = ID_ANI_MARIO_WALKING_RIGHT;
	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (nx >= 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			}
		}
		else
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
			}
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
		}
		else
		{
			aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
	}
	else if (isRaccoonAttacking)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
		}
		else
		{
			aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
		}
	}
	else if (vx == 0)
	{
		if (nx > 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
			}
		}
		else
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
		}
	}
	else if (vx > 0)
	{
		if (ax < 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
			}
		}
		else if (ax == MARIO_ACCEL_RUN_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
			}
		}
		else if (ax == MARIO_ACCEL_WALK_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
		}
	}
	else // vx < 0
	{
		if (ax > 0)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
			}
		}
		else if (ax == -MARIO_ACCEL_RUN_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
			}
		}
		else if (ax == -MARIO_ACCEL_WALK_X)
		{
			if (holdingObject)
			{
				aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT_GRABBING;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
		}
	}
	if (state == MARIO_ENDING_MOVE_RIGHT) aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
	if (aniId == -1)
	{
		aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
	}

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();


	animations->Get(aniId)->Render(x, y, 0, true);


	RenderBoundingBox();

}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE)

	{
		if (!deadTimerStarted)
		{
			dead_start = GetTickCount64();
			deadTimerStarted = true;
		}
			
		return;
	}
		

	switch (state)
	{
	case MARIO_STATE_TAIL_ATTACK_RIGHT:
		if (isSitting) break;
		vx = 0;
		ax = 0;
		nx = 1;
		raccoonAttack_start = GetTickCount64();
		isRaccoonAttacking = true;
		tailAttack->Attack(1);
		break;
	case MARIO_STATE_TAIL_ATTACK_LEFT:
		if (isSitting) break;
		vx = 0;
		ax = 0;
		nx = -1;
		raccoonAttack_start = GetTickCount64();
		isRaccoonAttacking = true;
		tailAttack->Attack(-1);
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;

		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;

		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;

		break;

	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;

		break;
	case MARIO_STATE_JUMP:

		if (isSitting) break;
		if (isOnPlatform && level != MARIO_LEVEL_RACCOON)
		{

			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;

		}
		else if (level == MARIO_LEVEL_RACCOON)
		{
			//(abs(this->vx) == MARIO_RUNNING_SPEED
			
			if (maxSpeedReached && flyTookOff) //Transition to fly
			{

				
				vy = -MARIO_JUMP_RUN_SPEED_Y;
				vyFlyMax = MARIO_RACCOON_MAX_FLY_VY_PHASE_2;
				flyTookOff = true;
				flyTookOffStart = GetTickCount64();
				
			}
			else if (maxSpeedReached && !isOnPlatform) //Flying. Keeping the gravity
			{

			
				isFlying = true;
				vyFlyMax = MARIO_RACCOON_MAX_FLY_VY_PHASE_2;
				ay = -MARIO_RACCOON_LIFT_GRAVITY;
			}
			
			else if (maxSpeedReached && isOnPlatform) //Normal fast jump
			{

				
				vy = -MARIO_JUMP_RUN_SPEED_Y;
				flyTookOff = true;
				flyTookOffStart = GetTickCount64();
				
			}
			else if (!maxSpeedReached && !isOnPlatform) //Descend
			{
				/*ay = MARIO_GRAVITY * 0.25;*/

				isDescending = true;
			}
			else if (isOnPlatform)
			{
				vy = -MARIO_JUMP_SPEED_Y;
				vyFlyMax = MARIO_RACCOON_MAX_FLY_VY_PHASE_1;
				flyTookOff = false;
				
			}
			lastJumpPressed = GetTickCount64();
			
		}

		break;

	case MARIO_STATE_RELEASE_JUMP:

		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:

		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:

		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:

		ax = 0.0f;
		
		vx = 0.0f;
		break;
	case MARIO_STATE_FACING_FRONT:
	

		break;
	
	case MARIO_STATE_FLY_RIGHT:
	{

		if (isOnPlatform)
		{
			vy = -MARIO_RACCOON_FLY_SPEED_Y;
			isFlying = true;
			ax = MARIO_ACCEL_FLY_X;
		}
		else
		{
			vy = -MARIO_JUMP_RUN_SPEED_Y;
			ax = MARIO_ACCEL_FLY_X;
		}
		break;
	}
	case MARIO_STATE_FLY_LEFT:
	{

	}
	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
	
		if (lives > 0)
			lives--;
		
		break;
	case MARIO_ENDING_MOVE_RIGHT:
		
		vy = 0;
		vx = MARIO_WALKING_SPEED;
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		scene->LockControl();
		end_level_walk_start = GetTickCount64();
		levelFinished= true;
		
		break;
	}

	CGameObject::SetState(state);
}




//Basically hitbox/ collision box.  left, top , right, bottom is basically the cord of the sprite. To modify, + to move it to the right, - to move it to the left
void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		if (isSitting)
		{
			left = x - MARIO_RACCOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACCOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACCOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
			bottom = top + MARIO_RACCOON_BBOX_HEIGHT;
		}

	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	//Setting level.
	level = l;
	if (this->level == MARIO_LEVEL_RACCOON)
	{
		/*ay = MARIO_RACCOON_GRAVITY;*/
	}
	else
	{
		ay = MARIO_GRAVITY;
	}
}

void CMario::TakeDamage()
{
	if (untouchable == 0)
	{
		if (level == MARIO_LEVEL_RACCOON)
		{
			level = MARIO_LEVEL_BIG;
			StartUntouchable();
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			//Die if small

			SetState(MARIO_STATE_DIE);
		}
	}
}


