#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include <string>
#include "HUD.h"
//#include "Koopas.h"
#define MAXIMUM_CAMERA_LIMIT 5
#define MAXIMUM_SCENE_TIME 300000

struct SceneCameraLimit
{
	float left;
	float top;
	float right;
	float bottom;
	float sky;
	
	SceneCameraLimit Empty()
	{
		SceneCameraLimit limit;
		limit.left = 0;
		limit.top = 0;
		limit.right = 0;
		limit.bottom = 0;
		limit.sky = 0;
		return limit;
	}
	bool operator== (const SceneCameraLimit& other)
	{
		return left == other.left && top == other.top && right == other.right && bottom == other.bottom && sky == other.sky;
	}
	SceneCameraLimit( float left, float top, float right, float bottom, float sky)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		this->sky = sky;
	}
	SceneCameraLimit()
	{
		this->left = 0;
		this->top = 0;
		this->right = 0;
		this->bottom = 0;
		this->sky = 0;
	}
	
};


class CPlayScene: public CScene
{
protected: 

	bool controlLocked = false;
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	vector <SceneCameraLimit> cameraLimits;
	SceneCameraLimit cameraLimit = SceneCameraLimit().Empty();
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_VARIABLES(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	bool cameraLocked = false;  //Change to only lock for cutscene and lock for control
	
	bool addedHud = false;
	HUD* hud = NULL;
	
	ULONGLONG sceneStartTime = -1;
	bool sceneStarted = false;
	
		

public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	bool ControlLocked() { return controlLocked; }
	
	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void AddObject (LPGAMEOBJECT object);
	void SwapObjectOrderToLast(LPGAMEOBJECT object);
	//Control
	bool ControlIsLocked() { return controlLocked; }
	void LockControl() { controlLocked = true;  DebugOut(L"Control locked"); }
	void UnlockControl() { controlLocked = false;  DebugOut (L"Control unlocked"); }
	void PlayDimscreenEffectFor(int time); //Dim in half time, then undim in half time
	void LockCamera() { cameraLocked = true; }
	void UnlockCamera() { cameraLocked = false; }

	void SwitchCameraLimit(int i) { cameraLimit = cameraLimits[i]; }
	int GetSceneID() { return id; }
	int HasHud () { return addedHud; }
	void AddHud(HUD* hud) { 
		this->hud = hud;
		addedHud = true;
		AddObject(hud);
		SwapObjectOrderToLast(hud);
	}
	int GetSceneTimeLeftInSecond() { 
		//If its negative, return 0. Else the number
		return (int)(MAXIMUM_SCENE_TIME - (GetTickCount64() - sceneStartTime)) / 1000 > 0 ? (int)(MAXIMUM_SCENE_TIME - (GetTickCount64() - sceneStartTime)) / 1000 : 0;

	
	}
};

typedef CPlayScene* LPPLAYSCENE;

