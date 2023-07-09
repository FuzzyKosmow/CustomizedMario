#include "Tunnel.h"
#include "Dimscreen.h"
void CTunnel::Render()
{
	if (height <= 0) return;

	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();


	s->Get(idSpriteTopBlockLeft)->Draw(x, y);
	s->Get(idSpriteTopBlockRight)->Draw(x + TUNNEL_TOP_BLOCK_WIDTH, y);
	for (int i = 1; i < height; i++)
	{
		s->Get(idSpriteBottomBlockLeft)->Draw(x, y + TUNNEL_TOP_BLOCK_HEIGHT + (i - 1) * TUNNEL_BOTTOM_BLOCK_HEIGHT);
		s->Get(idSpriteBottomBlockRight)->Draw(x + TUNNEL_TOP_BLOCK_WIDTH, y + TUNNEL_TOP_BLOCK_HEIGHT + (i - 1) * TUNNEL_BOTTOM_BLOCK_HEIGHT);
	}



}

void CTunnel::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TUNNEL_TOP_BLOCK_WIDTH / 2;
	t = y - TUNNEL_TOP_BLOCK_HEIGHT / 2;
	r = l + TUNNEL_TOP_BLOCK_WIDTH * 2;
	b = t + TUNNEL_TOP_BLOCK_HEIGHT + (height - 1) * TUNNEL_BOTTOM_BLOCK_HEIGHT;
}

void CTunnel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (canBeUsed && !travelling)
	{

		if (marioDetector->ObjectDetected())
		{
			CGame* game = CGame::GetInstance();
			LPSCENE scene = game->GetCurrentScene();
			CMario* mario = (CMario*)((CPlayScene*)scene)->GetPlayer();
			mario->SetOnTravelableTunnel(true);
			mario->SetTravelableTunnel(this);
			hasJustSetTravelable = true;
		}
		else
		{
			if (hasJustSetTravelable)
			{
				CGame* game = CGame::GetInstance();
				LPPLAYSCENE scene = (LPPLAYSCENE)game->GetCurrentScene();
				CMario* mario = (CMario*)((CPlayScene*)scene)->GetPlayer();
				mario->SetOnTravelableTunnel(false);
				hasJustSetTravelable = false;
				mario->SetTravelableTunnel(NULL);
				

			}
		}
	}
	else if (travelling)
	{
		if (travelFirstPhaseDone && travelSecondPhaseDone) //Total travel time consist of going up/down tunnel then dim screen and teleport somewhere else, undim screen then go up/down tunnel.
		{
			travelling = false;
			CGame* game = CGame::GetInstance();
			LPPLAYSCENE scene = (LPPLAYSCENE)game->GetCurrentScene();
			CMario* mario = (CMario*)scene->GetPlayer();
			mario->SetColliable();
			scene->UnlockControl();
			DebugOut(L"Finished travelling from time start %d\n", travel_start);
			
			canBeUsed = false;
			travel_start = 0;
			dimActivated = false;
			marioDetector->MakeInvisible();
			
		}
		else
		{
			float mx = 0, my = 0;
			CGame* g = CGame::GetInstance();
			LPPLAYSCENE scene = (LPPLAYSCENE)g->GetCurrentScene();
			CMario* mario = (CMario*)scene->GetPlayer();
			mario->GetPosition(mx, my);
			if (!travelFirstPhaseDone )
			{
				
				if (travelDown)
				{

			
					mario->SetPosition(mx, my + TUNNEL_TRAVEL_STEP*dt);
					travelledDistance += TUNNEL_TRAVEL_STEP*dt;
					
				}
				else
				{
	
					mario->SetPosition(mx, my - TUNNEL_TRAVEL_STEP);
					travelledDistance += TUNNEL_TRAVEL_STEP;
				}

				if (travelledDistance > TUNNEL_MAX_TRAVEL_DISTANCE)
				{
					travelFirstPhaseDone = true;
					travelledDistance = 0;
					
				}
			}
			else if (!dimActivated)
			{

				CDimScreenEffect::GetInstance()->MakeDimFor(TUNNEL_GO_DOWN_TIME, TUNNEL_DELAY_TIME, TUNNEL_GO_UP_TIME );
				dimActivated = true;
				dim_start = GetTickCount64();
			}
			else if (GetTickCount64() - dim_start > TUNNEL_GO_DOWN_TIME && !posSet)
			{
				mario->SetPosition(xDestination, yDestination);
				posSet = true;
				scene->UnlockCamera();
			}
			else if (GetTickCount64() - dim_start > TUNNEL_GO_DOWN_TIME + TUNNEL_DELAY_TIME && !travelSecondPhaseDone)
			{
				
				if (travelDown)
				{
					//Go up section
					mario->SetPosition(mx, my - TUNNEL_TRAVEL_STEP*dt);
				}
				else
				{
					mario ->SetPosition(mx, my + TUNNEL_TRAVEL_STEP*dt);
				}
				travelledDistance += TUNNEL_TRAVEL_STEP*dt;
				if (travelledDistance > TUNNEL_MAX_TRAVEL_DISTANCE)
				{
					travelSecondPhaseDone = true;
					travelledDistance = 0;
				}

			}
			
		
		}

	}
	CCollision::GetInstance()->Process(this, dt, coObjects);

}


void CTunnel::Travel()
{
	if (canBeUsed)
	{
		
			CGame* game = CGame::GetInstance();
			LPPLAYSCENE scene = (LPPLAYSCENE)game->GetCurrentScene();
			CMario* mario = (CMario*)((CPlayScene*)scene)->GetPlayer();
			scene->LockControl();
			scene->LockCamera();
			mario->SetState(MARIO_STATE_FACING_FRONT);
			travelling = true;
			travel_start = GetTickCount64();
			mario->SetUncolliable();
	
		
		
		
	}
}

