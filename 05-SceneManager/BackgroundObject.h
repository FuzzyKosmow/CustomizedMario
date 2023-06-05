#pragma once
#include "GameObject.h"
class CBackgroundObject : public CGameObject
{
protected:
			
	float cellWidth;
	float cellHeight;
	int spriteId;

public:
	CBackgroundObject(float x, float y,
		float cell_width, float cell_height,
		int sprite_id) :CGameObject(x, y)
	{
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteId = sprite_id;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Render();
	void Update(DWORD dt) {}
	
	
	int IsCollidable()
	{
		return -1;
	}
};