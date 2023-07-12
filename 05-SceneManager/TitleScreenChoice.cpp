#include "TitleScreenChoice.h"
#include "PlayScene.h"

CTitleChoice::CTitleChoice(float x, float y) : CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	
}

void CTitleChoice::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	int spriteID = -1;
	if (currentChoice == TITLE_STATE_CHOICE_1)
		spriteID = ID_SPRITE_TITLE_CHOICE_1;
	else
		spriteID = ID_SPRITE_TITLE_CHOICE_2;
	sprites->Get(spriteID)->Draw(x, y);
}


void CTitleChoice::SelectChoice()
{
	
	if (!selected)
	{
		selected = true;
		dim_start = GetTickCount();
		CDimScreenEffect::GetInstance()->MakeDimFor(TITLE_SCREEN_SELECT_DIM_TIME, TITLE_SCREEN_SELECT_DIM_DELAY, TITLE_SCREEN_SELECT_UNDIM_TIME);

	}
	
}



void  CTitleChoice::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (selected)
	{
		if (GetTickCount() - dim_start > TITLE_SCREEN_SELECT_DIM_TIME + TITLE_SCREEN_SELECT_DIM_DELAY)
		{
			
			CGame* game = CGame::GetInstance();
			game->InitiateSwitchScene(SCENE_ID_OVERWORLD);
		
		}
	}
}
