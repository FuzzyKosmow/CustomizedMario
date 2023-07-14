#pragma once

#include "GameObject.h"
#include "PlayScene.h"

#define DETECTION_ZONE_STATE_IDLE 0
#define DETECTION_ZONE_STATE_DETECTED 1
#define DETECTION_ZONE_CELL_WIDTH 15
#define DETECTION_ZONE_CELL_HEIGHT 15

//Mostly for static object to detect player
class SquareDetectionZone : public CGameObject {
	int width;
	bool playerDetected = false;
	float alpha = BBOX_ALPHA;
	bool visible = true;
public:
	SquareDetectionZone(float x, float y, int width) : CGameObject(x, y) {
		this->width = width;
		
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
		
		l = x - DETECTION_ZONE_CELL_WIDTH * width / 2.0f;
		t = y - DETECTION_ZONE_CELL_WIDTH * width / 2.0f;
		r = x + DETECTION_ZONE_CELL_WIDTH * width / 2.0f;
		b = y + DETECTION_ZONE_CELL_WIDTH * width / 2.0f;
	}
	void RenderBoundingBox();
	void MakeVisible() { visible = true; }
	void MakeInvisible() { visible = false; }
	bool PlayerDetected() { return playerDetected; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int GetObjectType() { return OBJECT_TYPE_DETECTION_ZONE; }
};


//A tiny bit more advanced that allow to detect using object type, looks rather resource heavy , yikes
class ObjectDetector : public CGameObject {

	vector<LPGAMEOBJECT> detectedObjects;
	int width;
	int height;
	int type;
	bool objectDetected = false;
	bool visible = false;
	float alpha = BBOX_ALPHA;
public:
	ObjectDetector(float x, float y, int width, int height, int type) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->type = type;
	}
	ObjectDetector() {};
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
		l = x - DETECTION_ZONE_CELL_WIDTH * width / 2;
		t = y - DETECTION_ZONE_CELL_HEIGHT * height / 2;
		r = l + DETECTION_ZONE_CELL_WIDTH * width;
		b = t + DETECTION_ZONE_CELL_HEIGHT * height;
	}
	void MakeVisible() { visible = true; }
	void MakeInvisible() { visible = false; }
	bool ObjectDetected() { return objectDetected; }
	void RenderBoundingBox();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	vector<LPGAMEOBJECT> GetDetectedObjects() { return detectedObjects; }

	int GetObjectType() { return OBJECT_TYPE_DETECTION_ZONE; } //No purpose in differenating them yet
};
