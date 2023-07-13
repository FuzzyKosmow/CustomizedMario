#pragma once
#include "GameObject.h"




class HUD : public CGameObject
{
	static  HUD* __instance;
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

	int GetObjectType() { return OBJECT_TYPE_HUD; }

};