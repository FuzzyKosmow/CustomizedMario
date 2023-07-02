#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Collision.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"
#include "Detection.h"
#define EATING_PLANT_STATE_IDLE 0
#define EATING_PLANT_STATE_SHOWING 1
#define EATING_PLANT_STATE_SHOWN 2
#define EATING_PLANT_STATE_RETRACT 3

//EATING plant stats
#define EATING_PLANT_IDLE_TIME 1000
#define EATING_PLANT_SHOW_TIME 1000
#define EATING_PLANT_SHOWN_TIME 1000
#define EATING_PLANT_RETRACT_TIME 1000
#define EATING_PLANT_SHOW_HEIGHT_DIFFERENCE 50
#define EATING_PLANT_BBOX_HEIGHT 32
#define EATING_PLANT_BBOX_WIDTH 16
#define EATING_PLANT_DETECTION_ZONE_SIZE 20

class CEatingPlant : public CGameObject {
protected:
	//Time trackers
	ULONGLONG show_start = 0;
	ULONGLONG retract_start = 0;
	ULONGLONG shown_start = 0;
	ULONGLONG idle_start = 0;

	float baseX; //Defalt position
	float baseY;
	int detectionZoneSize = EATING_PLANT_DETECTION_ZONE_SIZE;
	//Detectionzone, only make make the plant start working when mario is in within view
	SquareDetectionZone* dZone;
public:
	int IsBlocking() { return 0; };
	int IsCollidable() { return 1; }
	CEatingPlant(float x, float y) : CGameObject(x, y) {

		SetState(EATING_PLANT_STATE_IDLE);
		dZone = new SquareDetectionZone(x - detectionZoneSize / 2 * 16, y - detectionZoneSize / 2 * 16, detectionZoneSize);
		dZone->MakeInvisible();
		baseX = x;
		baseY = y;
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(dZone);

	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int GetObjectType() { return OBJECT_TYPE_EATING_PLANT; }
};


