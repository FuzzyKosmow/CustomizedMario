#include <algorithm>
#include "debug.h"

#include "Mario.h"
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

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	DebugOutTitle(L"coin: %d", coin);
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
			holdingObject = false;
			holdObject = nullptr;
		}

		
	}

	if (!isFlying) //Since only raccoon can fly
	{
		ay = MARIO_GRAVITY;
	}
	vy += ay * dt;
	vx += ax * dt;
	
	if (isOnPlatform)
	{
		isFlying = false;


	}
	if (abs(vx) > abs(maxVx))
	{
		vx = maxVx;
		maxSpeedReached = true;
	}
	else
	{
		maxSpeedReached = false;
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
		else
		{
			//Render the attack zone and handle collison
			
		}
	}
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
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
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
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
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CShroom*>(e->obj))
		OnCollisionWithSchroom(e);
	else if	(dynamic_cast<PlantProjectile*>(e->obj))
		OnCollisionWithPlantBullet(e);
	else if (dynamic_cast<CShootingPlant*> (e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CTurtle*> (e->obj))
		OnCollisionWithTurtle(e);
	
	
	
		
}
void CMario::OnCollisionWithTurtle(LPCOLLISIONEVENT e)
{
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);
	LPGAME game = CGame::GetInstance();
	if (e->ny < 0)
	{
		if (turtle->GetState() == TURTLE_STATE_WALKING)
		{
			turtle->SetState(TURTLE_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (turtle->GetState() == TURTLE_STATE_SHELL)
		{
			turtle->SetState(TURTLE_STATE_SHELL_MOVING);
			if (e->nx > 0 )
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
	}
	else if (e->nx !=0 && turtle->GetState() == TURTLE_STATE_SHELL  && 
		game->IsKeyDown(DIK_A)
		)
	{
		if (!holdingObject)
		{
			holdingObject = true;
			holdObject = turtle;
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
	TakeDamage();
	
}


void CMario::OnCollisionWithBigColorBrick(LPCOLLISIONEVENT e)
{

		// If Mario jumps from below, allow mario to be on top of the brick
	if (e->ny > 0 ) {
		if (e->obj->IsBlocking())
		{
			vy = 0;
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
		
	}
}
void CMario::OnCollisionWithSchroom(LPCOLLISIONEVENT e)
{
	if (state == MARIO_STATE_DIE) return;
	if ((GetLevel() == MARIO_LEVEL_SMALL || GetLevel() == MARIO_LEVEL_BIG) && dynamic_cast<CShroom*>(e->obj)->GetState() == SHROOM_STATE_WALKING)
	{
		SetLevel(MARIO_LEVEL_BIG);
		e->obj->Delete();
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
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
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
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
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
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
			{
				if (holdingObject)
				{
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
				}
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				
			}
				
			else
			{
				if (holdingObject)
				{
					aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
				}
				else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
				
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
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
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
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

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
		}
	}
	else
		
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
		{
			//Set aniID to raccoon attack accordingly if mario is attacking
			if (isRaccoonAttacking)
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
			else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}
		}
			
	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
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
	
	
	animations->Get(aniId)->Render(x, y);

	
	RenderBoundingBox();
	
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_TAIL_ATTACK_RIGHT:
		if (isSitting) break;
		vx = 0;
		ax = 0;
		
		nx = 1;
		raccoonAttack_start = GetTickCount64();
		isRaccoonAttacking = true;
		break;
	case MARIO_STATE_TAIL_ATTACK_LEFT:
		if (isSitting) break;
		vx = 0;
		ax = 0;
		nx = -1;
		raccoonAttack_start = GetTickCount64();
		isRaccoonAttacking = true;
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
			
			if (abs(this->vx) == MARIO_RUNNING_SPEED && !isOnPlatform)
			{
				
				vy = -MARIO_RACCOON_FLY_SPEED_Y;
				ay = MARIO_RACCOON_GRAVITY;
			}
				
			else if (isOnPlatform)
			{
				
				vy = -MARIO_JUMP_SPEED_Y;
				ay = MARIO_RACCOON_GRAVITY;
			}
			isFlying = true;
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
void CMarioTailAttack::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (nx >= 0)
	{
		//Render on the right side
		left = 10 + x - MARIO_BIG_BBOX_WIDTH / 2;
		top =  y - MARIO_BIG_BBOX_HEIGHT / 2;
		right = 10+left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		//On the left side
		left = -10 + x - MARIO_BIG_BBOX_WIDTH / 2;
		top = y - MARIO_BIG_BBOX_HEIGHT / 2;
		right = -10 + left + MARIO_BIG_BBOX_WIDTH;
		bottom = top + MARIO_BIG_BBOX_HEIGHT;
	}
}

void CMarioTailAttack::OnNoCollision(DWORD dt)
{
	//Do nothing
}

void CMarioTailAttack::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBrick*> (e->obj))
	{
		e->obj->Delete();
	}
}


