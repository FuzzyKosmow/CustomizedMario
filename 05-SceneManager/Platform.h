#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public: 
	CPlatform(float x, float y,
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

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int GetObjectType () { return OBJECT_TYPE_PLATFORM; }
};

typedef CPlatform* LPPLATFORM;


class CVerticalObject : public CGameObject
{
protected:
	int height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int blocking = 1;

public:
	CVerticalObject(float x, float y,
		float cell_width, float cell_height, int height,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end,
		int blockinging = 1
	) :CGameObject(x, y)
	{
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this -> blocking = blockinging;
	}

	void Render();
	void Update(DWORD dt) {}
	int IsBlocking() { return blocking; }
	void SetBlocking(int blocking) { this->blocking = blocking; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int GetObjectType() { return OBJECT_TYPE_VERTICAL_OBJECT; }
	

};


class PassablePlatform : public CPlatform
{

public:
	virtual int IsDirectionColliable(float nx, float ny)
	{
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}
	int GetObjectType() { return OBJECT_TYPE_PASSABLE_PLATFORM; }
};