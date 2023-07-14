#pragma once
#include "LootBrick.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"
#include "Leaf.h"
#include "Greenshroom.h"
void CLootBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	
	
	if (lootState == LOOT_BRICK_STATE_NOT_LOOTED && spriteType == LOOT_BRICK_SPRITE_TYPE_QUESTION_MARK) {
		animations->Get(ID_ANI_LOOT_BRICK)->Render(x, y);
	}
	else if (lootState == LOOT_BRICK_STATE_NOT_LOOTED && spriteType == LOOT_BRICK_SPRITE_TYPE_BRICK)
	{
		animations->Get(ID_ANI_LOOT_BRICK_TYPE_BRICK)->Render(x, y);
	}
	else if (lootState == LOOT_BRICK_STATE_LOOTED) {
		animations->Get(ID_ANI_LOOT_BRICK_LOOTED)->Render(x, y);
	}
	
	//RenderBoundingBox();
}
void CLootBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Show the loot slowly if not coin
	if (lootShowComplete == false && lootState == LOOT_BRICK_STATE_LOOTED)
	{
		if (lootType != LOOT_TYPE_COIN)
		{
			if (GetTickCount64() - timeStartToShowLoot > LOOT_BRICK_TIME_TO_SHOW_LOOT) {
				lootShowComplete = true;
				EnableLoot();
			}
			else {

				float lootOldY = 0;
				float lootOldX = 0;
				loot->GetPosition(lootOldX, lootOldY);
				float heightAddEachFrame = (1000.0f / MAX_FRAME_RATE) * BRICK_AND_LOOT_HEIGHT_DIFF / LOOT_BRICK_TIME_TO_SHOW_LOOT;
				loot->SetPosition(lootOldX, lootOldY - heightAddEachFrame);
			}
		}
		else {
			if (GetTickCount64() - timeStartToShowLoot > LOOT_BRICK_TIME_TO_SHOW_COIN) {
				lootShowComplete = true;
				EnableLoot();
			}
			else {

				float lootOldY = 0;
				float lootOldX = 0;
				loot->GetPosition(lootOldX, lootOldY);
				float heightAddEachFrame = (1000.0f / MAX_FRAME_RATE) * (BRICK_AND_COIN_HEIGHT_DIFF) / LOOT_BRICK_TIME_TO_SHOW_COIN;
				loot->SetPosition(lootOldX, lootOldY - heightAddEachFrame);
			}
			
		}
		
	}
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLootBrick::ShowLoot() //Slowly show the loot, from down to top. Has built in score
{
	if (lootState == LOOT_BRICK_STATE_NOT_LOOTED) {
		lootState = LOOT_BRICK_STATE_LOOTED;
		timeStartToShowLoot = GetTickCount64();
		HUD::GetInstance()->PopUpScoreAtMario(BRICK_BREAK_SCORE);
	}
	
}


void CLootBrick::EnableLoot() //Enable state of the actual loot
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	//Swap the loot to the last so that it render correctly
	scene->SwapObjectOrderToLast(loot);
	if (lootType == LOOT_TYPE_MUSHROOM) {
		CShroom* shroom = dynamic_cast <CShroom*>(loot);

		shroom->SetState(SHROOM_STATE_WALKING);

	}
	else if (lootType == LOOT_TYPE_COIN) {
		CCoin* coin = dynamic_cast <CCoin*>(loot);
		CMario* mario = (CMario*) ((LPPLAYSCENE) CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->AddCoin(1);
		loot->Delete();
		
		
	}
	else if (lootType == LOOT_TYPE_LEAF) {
		CLeaf* leaf = dynamic_cast <CLeaf*>(loot);
		leaf->SetState(LEAF_STATE_FLYING);
	}
	else if (lootType == LOOT_TYPE_GREEN_MUSHROOM)
	{
		CGreenshroom* greenShroom = dynamic_cast <CGreenshroom*>(loot);
		greenShroom->SetState(SHROOM_STATE_WALKING);
	}
}


void CLootBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LBRICK_BBOX_WIDTH / 2;
	t = y - LBRICK_BBOX_HEIGHT / 2;
	r = l + LBRICK_BBOX_WIDTH;
	b = t + LBRICK_BBOX_HEIGHT;
}

