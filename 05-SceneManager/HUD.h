#pragma once
#include "GameObject.h"

#define DEFAULT_HUD_NUMBER_DRAWER_MAX_LENGTH 3


class HUD : public CGameObject
{
	static  HUD* __instance;






	float marioIconX = 0;
	float marioIconY = 0;
	
	
public:
	HUD();
	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};



	void CreateScoreAtMario(int number);
	void Unload()
	{
		delete __instance;
		__instance = NULL;
		DebugOut(L"[HUD] Hud removed\n");

	}
	static  HUD* GetInstance();
	void QuickUpdate(float x, float y);
	int GetObjectType() { return OBJECT_TYPE_HUD; }
	void DrawNumberAt(int number, float x, float y, int maxNumOfDigit = DEFAULT_HUD_NUMBER_DRAWER_MAX_LENGTH);

	void PopUpScoreAtMario(int number);

};


#define HUD_POPUP_SCORE_TIME 500
#define HUD_POPUP_SCORE_SPEED_Y 0.03f
class PopUpScore : public CGameObject
{
	
	int score = 0;
	ULONGLONG timeStart = 0;
	int scoreDigits = 0;
public:
	PopUpScore(float x, float y, int score);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int GetObjectType() { return OBJECT_TYPE_SCORE; }
};

int NumberDigits(int number);