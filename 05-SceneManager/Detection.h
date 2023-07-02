#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "PlayScene.h"
#include "Mario.h"
#include "AssetIDs.h"
#define DETECTION_ZONE_STATE_IDLE 0
#define DETECTION_ZONE_STATE_DETECTED 1
#define DETECTION_ZONE_CELL_WIDTH 16
#define DETECTION_ZONE_CELL_HEIGHT 16
class SquareDetectionZone : public CGameObject {
	int width;
	bool playerDetected = false;
	float alpha = BBOX_ALPHA;
	bool visible = true;
public:
	SquareDetectionZone(float x, float y, int width ) : CGameObject(x, y) {
		this->width = width;
		SetState(DETECTION_ZONE_STATE_IDLE);
	}
	SquareDetectionZone() {};
	void Render()
	{
		if (visible)
			RenderBoundingBox();
		else
			return;
	}
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - DETECTION_ZONE_CELL_WIDTH / 2;
		t = y - DETECTION_ZONE_CELL_HEIGHT / 2;
		r = l + DETECTION_ZONE_CELL_WIDTH * width;
		b = t + DETECTION_ZONE_CELL_HEIGHT * width;
	}
	void RenderBoundingBox();
	void MakeVisible() { visible = true; }
	void MakeInvisible() { visible = false; }
	bool PlayerDetected() { return playerDetected; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int GetObjectType() { return OBJECT_TYPE_DETECTION_ZONE; }
};


//Square zone that detect the type of object, store all the detected object in a vector
class ObjectDetector : public CGameObject {

vector<LPGAMEOBJECT> detectedObjects;
	int width;
	int height;
	int type;
	bool objectDetected = false;

public:
ObjectDetector(float x, float y, int width, int height, int type) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->type = type;
	}
	ObjectDetector() {};
	void Render()
	{
		RenderBoundingBox();
	}
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - DETECTION_ZONE_CELL_WIDTH / 2;
		t = y - DETECTION_ZONE_CELL_HEIGHT / 2;
		r = l + DETECTION_ZONE_CELL_WIDTH * width;
		b = t + DETECTION_ZONE_CELL_HEIGHT * width;
	}
	void RenderBoundingBox();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	vector<LPGAMEOBJECT> GetDetectedObjects() { return detectedObjects; }
	void ClearDetectedObjects() { detectedObjects.clear(); }
};
