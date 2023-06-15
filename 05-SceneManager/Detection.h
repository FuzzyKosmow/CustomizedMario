#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "PlayScene.h"


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
	SquareDetectionZone(float x, float y, float width) : CGameObject(x, y) {
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
};