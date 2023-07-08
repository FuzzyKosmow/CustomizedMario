#pragma once
#include "Game.h"
#include "GameObject.h"

#define	ID_TEXTURE_DIMSCREEN -200

class CDimScreenEffect : public CGameObject
{

	static CDimScreenEffect* __instance;
	 DWORD dimTime = 0;
	 DWORD undimTime = 0;
	 DWORD delayTime = 0;

	 DWORD dimStart = 0;
	 DWORD undimStart = 0;
	 DWORD delayStart = 0;
	 float alpha = 0;

	 bool doneDimming = false;
	 bool doneUndimming = false;
	 bool doneDelaying = false;
	 bool enabled = false;
	public:
		CDimScreenEffect();
		
		int IsCollidable() { return 0; };
		int IsBlocking() { return 0; };
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
		
	
		void MakeDimFor(DWORD dimTime, DWORD delayTime,DWORD undimTime);
		static CDimScreenEffect* GetInstance();
		int GetObjectType() { return OBJECT_TYPE_SYSTEM; };

};