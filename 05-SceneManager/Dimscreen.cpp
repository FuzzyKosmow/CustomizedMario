#pragma once
#include "Dimscreen.h"
#include "Textures.h"
#include "PlayScene.h"
CDimScreenEffect::CDimScreenEffect() 
{
	__instance = this;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(this);
}


void CDimScreenEffect::Render()
{
	if (enabled)
	{
		LPTEXTURE tex = CTextures::GetInstance()->Get(ID_TEXTURE_DIMSCREEN);
		LONG screenHeight = CGame::GetInstance()->GetBackBufferHeight();
		LONG screenWidth = CGame::GetInstance()->GetBackBufferWidth();
		D3DXVECTOR3 p(x, y, 0);
		RECT rect;

		rect.left = 0;
		rect.top = 0;
		rect.right = screenWidth * 2; //To make sure it cover the whole screen regardless of where the camera is
		rect.bottom =  screenHeight*2;
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);
		float marioX, marioY; 
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		CMario* mario = (CMario*)scene->GetPlayer();
		mario->GetPosition(marioX, marioY);
		CGame::GetInstance()->Draw(marioX-cx, marioY-cy, tex, &rect, alpha);
		

		
	}
}



void CDimScreenEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (enabled)
	{
		
		if (!doneDimming)
		{
			DWORD now = GetTickCount();
			if (now - dimStart >= dimTime)
			{
				doneDimming = true;
				undimStart = now;
			}
			else
			{
				//Slowly go from 0 -> 1
				alpha = (now - dimStart) / (float)dimTime;
			}
		}
		else if (!doneDelaying)
		{
			DWORD now = GetTickCount();
			if (now - undimStart >= delayTime)
			{
				doneDelaying = true;
				undimStart = now;
			}
		}
		else if (!doneUndimming)
		{
			DWORD now = GetTickCount();
			if (now - undimStart >= undimTime)
			{
				doneUndimming = true;
				enabled = false;
			}
			else
			{
				//Slowly go from 1-> 0
				alpha = 1 - (now - undimStart) / (float)undimTime;
			}
		}
	}
	else
	{
		doneDimming = false;
		doneUndimming = false;
		alpha = 0;
	}
	
}

void CDimScreenEffect::MakeDimFor(DWORD dimTime, DWORD delayTime,DWORD undimTime)
{
	enabled = true;
	this->dimTime = dimTime;
	this ->delayTime = delayTime;
	this->undimTime = undimTime;
	dimStart = GetTickCount();

}

CDimScreenEffect* CDimScreenEffect::__instance = NULL;
CDimScreenEffect* CDimScreenEffect::GetInstance()
{
	if (__instance == NULL) __instance = new CDimScreenEffect();
	return __instance;
}