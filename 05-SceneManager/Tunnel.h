#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Detection.h"

#define BRICK_WIDTH 16
#define TUNNEL_TOP_BLOCK_WIDTH 15
#define TUNNEL_TOP_BLOCK_HEIGHT 15
#define TUNNEL_BOTTOM_BLOCK_WIDTH 14
#define TUNNEL_BOTTOM_BLOCK_HEIGHT 15
#define TUNNEL_COLOR_MID_GREEN 2


//Sprites
#define ID_SPRITE_TOP_BLOCK_LEFT_MID_GREEN 100001
#define ID_SPRITE_TOP_BLOCK_RIGHT_MID_GREEN 100002
#define ID_SPRITE_BOTTOM_BLOCK_LEFT_MID_GREEN 100003
#define ID_SPRITE_BOTTOM_BLOCK_RIGHT_MID_GREEN 100004
class CTunnel : public CGameObject {

	protected:
		int height; //How tall is the thing
		
		int color;
		int idSpriteTopBlockLeft;
		int  idSpriteTopBlockRight;
		int idSpriteBottomBlockLeft;
		int idSpriteBottomBlockRight;
		bool canBeUsed = false; //If the tunnel can be used, stand on top of it and press S (jump) to move to the next scene
		ObjectDetector* marioDetector = NULL;
		bool hasJustSetTravelable = false;
public:
	CTunnel(float x, float y, int color, int height, bool usable = false) {
		this->x = x;
		this->y = y;
		this->color = color;
		this->height = height;
		canBeUsed = usable;
		if (canBeUsed)
		{
			marioDetector = new ObjectDetector(x + TUNNEL_TOP_BLOCK_WIDTH/2, y - TUNNEL_TOP_BLOCK_HEIGHT,2,1, OBJECT_TYPE_MARIO);
			marioDetector->MakeVisible();
			LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			scene->AddObject(marioDetector);
			

		}
		switch (color)
		{
		case TUNNEL_COLOR_MID_GREEN:
		{
			idSpriteTopBlockLeft = ID_SPRITE_TOP_BLOCK_LEFT_MID_GREEN;
			idSpriteTopBlockRight = ID_SPRITE_TOP_BLOCK_RIGHT_MID_GREEN;
			idSpriteBottomBlockLeft = ID_SPRITE_BOTTOM_BLOCK_LEFT_MID_GREEN;
			idSpriteBottomBlockRight = ID_SPRITE_BOTTOM_BLOCK_RIGHT_MID_GREEN;

		}
		}
		
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetObjectType () { return OBJECT_TYPE_TUNNEL; }

};