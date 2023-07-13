#include "HUD.h"
#include "PlayScene.h"


//Render
void HUD::Render()
{
	//Render general hud zone 
	CSprites * s = CSprites::GetInstance();
	
	s->Get(ID_SPRITE_HUD_GENERAL)->Draw(x, y);
}


void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	////Update position to follow camera
	//CGame* game = CGame::GetInstance();
	//float cx, cy;
	//game->GetCamPos(cx, cy);
	//this->x = cx+150;
	//this->y = cy+230;
}

HUD::HUD()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(this);
	scene->SwapObjectOrderToLast(this);
}

HUD* HUD::__instance = NULL;
HUD* HUD::GetInstance() //Also add to non-intro scene if the hud is not added yet
{
	
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}
