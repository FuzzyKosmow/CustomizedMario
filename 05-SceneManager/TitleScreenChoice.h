#pragma once
#include "GameObject.h"
#include "Dimscreen.h"
#define TITLE_STATE_CHOICE_1 1
#define TITLE_STATE_CHOICE_2 2


#define ID_SPRITE_TITLE_CHOICE_1 600004
#define ID_SPRITE_TITLE_CHOICE_2 600005

#define TITLE_SCREEN_SELECT_DIM_TIME 300
#define TITLE_SCREEN_SELECT_DIM_DELAY 300
#define TITLE_SCREEN_SELECT_UNDIM_TIME 100


class CTitleChoice : public CGameObject
{
	int currentChoice = TITLE_STATE_CHOICE_1;


	bool selected = false;

	ULONGLONG dim_start = 0;
	bool dimm_started = 0;
	
public:
	CTitleChoice(float x, float y);
	~CTitleChoice();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	void SetState(int state) {};

	int GetCurrentChoice() { return currentChoice; }
	void MoveChoiceUp()
	{
		//No more than 2 and no less than 1
		if (currentChoice < 2)
			currentChoice++;
		else if (currentChoice == 2)
			currentChoice = 1;
	}
	void MoveChoiceDown()
	{
		//No more than 2 and no less than 1
		if (currentChoice > 1)
			currentChoice--;
		else if (currentChoice == 1)
			currentChoice = 2;
	}
	int GetChoice() { return currentChoice; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SelectChoice();
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	int GetObjectType() { return OBJECT_TYPE_SCREEN_TITLE_CHOICE; }
};