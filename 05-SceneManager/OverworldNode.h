#pragma once

#include "GameObject.h"
#include "Detection.h"


#define OVERWORLD_BLOCKING_OBJECT_BBOX_WIDTH  15
#define OVERWORLD_BLOCKING_OBJECT_BBOX_HEIGHT 15

class COverworldNode : public CGameObject
{
	int sceneIdToLoad = -1;
	ObjectDetector* marioDetector = NULL;
	int spriteID = -1;
	bool hasJustSetNode = false;

public:
	COverworldNode(float x, float y, int spriteID, int sceneIDToLoad);
	void GetBoundingBox (float& l, float& t, float& r, float& b) {};

	int IsColliable() { return 0; };
	int IsBlocking() { return 1; };
	void Render();
	void Update (DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SwitchScene();
	int GetObjectType() { return OBJECT_TYPE_OVERWORLD_NODE; }
};

