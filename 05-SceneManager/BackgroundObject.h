#pragma once
#include "GameObject.h"
class CBackgroundObject : public CGameObject
{
	//Similiar to plaform, but non-colliable.
protected:
			
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Render();
	void Update(DWORD dt) {}
	void RenderBoundingBox() {}
	CBackgroundObject(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}
	
	int IsCollidable()
	{
		return -1;
	}
};