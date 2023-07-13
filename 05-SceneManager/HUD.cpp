#include "HUD.h"
#include "PlayScene.h"

#define HUD_MARIO_ICON_OFFSET_X -134
#define HUD_MARIO_ICON_OFFSET_Y 6

#define HUD_WORLD_OFFSET_X -134
#define HUD_WORLD_OFFSET_Y 6

#define HUD_SCORE_OFFSET_X -60
#define HUD_SCORE_OFFSET_Y 6

#define HUD_TIME_OFFSET_X 12
#define HUD_TIME_OFFSET_Y 6
#define HUD_TIME_MAX_CHAR 3


#define HUD_NUMBER_WIDTH	10

#define CURRENT_WORLD 1

//Render
void HUD::Render()
{
	//Render general hud zone 
	CSprites * s = CSprites::GetInstance();
	
	s->Get(ID_SPRITE_HUD_GENERAL)->Draw(x, y);
	s->Get(ID_SPRITE_HUD_MARIO_ICON)->Draw(x+ HUD_MARIO_ICON_OFFSET_X, y+ HUD_MARIO_ICON_OFFSET_Y);
	
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	int timeLeft = scene->GetSceneTimeLeftInSecond();
	
	DrawNumberAt(timeLeft, x + HUD_TIME_OFFSET_X, y + HUD_TIME_OFFSET_Y, HUD_TIME_MAX_CHAR);
}


void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	////Update position to follow camera
	//CGame* game = CGame::GetInstance();
	//float cx, cy;
	//game->GetCamPos(cx, cy);
	//this->x = cx+150;
	//this->y = cy+230;
	//Update random number from 1-10 and back to 1 again
	if (GetTickCount64() - lastRandomNumberChangeTime > 1000)
	{
		randomNumber = rand() % 10 + 1;
		lastRandomNumberChangeTime = GetTickCount64();
	}
}


void HUD::QuickUpdate(float x, float y)
{
	this->x = x;
	this->y = y;
	/*DrawNumberAt (CURRENT_WORLD, x + HUD_WORLD_OFFSET_X, y + HUD_WORLD_OFFSET_Y, 2);*/
	CSprites * s = CSprites::GetInstance();
	
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


void HUD::DrawNumberAt(int number, float x, float y, int maxNumOfDigit)
{
	//Draw number at x,y
	//Get the number of digits
	int numOfDigit = 0;
	int temp = number;
	while (temp > 0)
	{
		temp /= 10;
		numOfDigit++;
	}
	//Draw the number
	CSprites* sprites = CSprites::GetInstance();
	for (int i = 0; i < maxNumOfDigit; i++)
	{
		int digit = number % 10;
		sprites->Get(ID_SPRITE_HUD_NUMBER_0 + digit)->Draw(x + (maxNumOfDigit - i - 1) * HUD_NUMBER_WIDTH, y);
		number /= 10;
	}
}