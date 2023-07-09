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
#define TUNNEL_COLOR_BLACK_INVERTED 3

//Sprites
#define ID_SPRITE_TOP_BLOCK_LEFT_MID_GREEN 100001
#define ID_SPRITE_TOP_BLOCK_RIGHT_MID_GREEN 100002
#define ID_SPRITE_BOTTOM_BLOCK_LEFT_MID_GREEN 100003
#define ID_SPRITE_BOTTOM_BLOCK_RIGHT_MID_GREEN 100004

#define ID_SPRITE_TOP_BLOCK_LEFT_BLACK 101300
#define ID_SPRITE_TOP_BLOCK_RIGHT_BLACK 101301
#define ID_SPRITE_BOTTOM_BLOCK_LEFT_BLACK 101302
#define ID_SPRITE_BOTTOM_BLOCK_RIGHT_BLACK 101303

//Stats for getting in and out of tunnel

#define TUNNEL_TRAVEL_TIME_TO_FINISH_ANIMATION 1000 //How long does it take to finish animation to go up or down tunnel

#define TUNNEL_MAX_TRAVEL_DISTANCE 30
#define TUNNEL_TRAVEL_STEP 0.1


#define TUNNEL_TYPE_GO_DOWN_WITH_TRIGGER 1
#define TUNNEL_TYPE_GO_UP_WITH_TRIGGER 2

#define TUNNEL_GO_DOWN_TIME 1000
#define TUNNEL_DELAY_TIME 1200
#define TUNNEL_GO_UP_TIME 200

#define TUNNEL_MOVE_MARIO_DOWN_TIME_ESTIMATION 500
#define TUNNEL_MOVE_MARIO_UP_TIME_ESTIMATION 500

#define	TUNNEL_MARIO_DETECTOR_WIDTH_UNIT 2
#define	TUNNEL_MARIO_DETECTOR_HEIGHT_UNIT 2

#define TUNNEL_TRAVEL_TIME TUNNEL_MOVE_MARIO_DOWN_TIME_ESTIMATION + TUNNEL_MOVE_MARIO_UP_TIME_ESTIMATION + TUNNEL_DELAY_TIME + TUNNEL_GO_DOWN_TIME + TUNNEL_GO_UP_TIME
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
	
		float xDestination = 0;
		float yDestination = 0;

		bool firstPhaseTravelDown = true;
		bool secondPhaseTravelDown = false;
		
		bool travelling = false;
		
		bool finishedTravelling = false;
		ULONGLONG travel_start = 0;
		float travelledDistance = 0;

		bool dimActivated = false;
		ULONGLONG dim_start = 0;
		bool posSet = false;

		bool travelFirstPhaseDone = false;
		bool travelSecondPhaseDone = false;

		int cameraLimitToSwitchTo = 0; //Immeadiately after dimmed, switch to this camera limit
		bool isInverted = false;
		
public:
	CTunnel(float x, float y, int color, int height, bool usable = false,
		bool inverted = false,
		bool firstPhaseGoDown = true, bool secondPhaseGoDown = false,
		float xDestination = 2405, float yDestination = 180,
		int cameraLimitToSwitchTo = 0
		
	) {
		this->x = x;
		this->y = y;
		this->color = color;
		this->height = height;
		canBeUsed = usable;
		if (canBeUsed)
		{
			if (inverted)
			{
				marioDetector = new ObjectDetector(x + TUNNEL_TOP_BLOCK_WIDTH / 2, y + TUNNEL_TOP_BLOCK_HEIGHT/ 2  + TUNNEL_TOP_BLOCK_HEIGHT * height, TUNNEL_MARIO_DETECTOR_WIDTH_UNIT, TUNNEL_MARIO_DETECTOR_HEIGHT_UNIT, OBJECT_TYPE_MARIO);
				marioDetector->MakeVisible();
				this->isInverted = true;
			}
			else
			{
				
				marioDetector = new ObjectDetector(x + TUNNEL_TOP_BLOCK_WIDTH / 2, y - TUNNEL_TOP_BLOCK_HEIGHT, TUNNEL_MARIO_DETECTOR_WIDTH_UNIT, TUNNEL_MARIO_DETECTOR_HEIGHT_UNIT, OBJECT_TYPE_MARIO);
				marioDetector->MakeVisible();
				this->isInverted = false;
			}
			
			LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			scene->AddObject(marioDetector);

			this->xDestination = xDestination;
			this->yDestination = yDestination;
			if (firstPhaseGoDown)
			{
				firstPhaseTravelDown = true;
		
			}
			else
			{
				firstPhaseTravelDown = false;

			}
			if (secondPhaseGoDown)
			{
				secondPhaseTravelDown = true;
			}
			else
			{
				secondPhaseTravelDown = false;
			}

		}
		this->cameraLimitToSwitchTo = cameraLimitToSwitchTo;
		switch (color)
		{
		case TUNNEL_COLOR_MID_GREEN:
		{
			idSpriteTopBlockLeft = ID_SPRITE_TOP_BLOCK_LEFT_MID_GREEN;
			idSpriteTopBlockRight = ID_SPRITE_TOP_BLOCK_RIGHT_MID_GREEN;
			idSpriteBottomBlockLeft = ID_SPRITE_BOTTOM_BLOCK_LEFT_MID_GREEN;
			idSpriteBottomBlockRight = ID_SPRITE_BOTTOM_BLOCK_RIGHT_MID_GREEN;
			break;
		}
		case TUNNEL_COLOR_BLACK_INVERTED:
		{
			idSpriteTopBlockLeft = ID_SPRITE_TOP_BLOCK_LEFT_BLACK;
			idSpriteTopBlockRight = ID_SPRITE_TOP_BLOCK_RIGHT_BLACK;
			idSpriteBottomBlockLeft = ID_SPRITE_BOTTOM_BLOCK_LEFT_BLACK;
			idSpriteBottomBlockRight = ID_SPRITE_BOTTOM_BLOCK_RIGHT_BLACK;
			
			break;
		}
		}
		
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	int GetObjectType () { return OBJECT_TYPE_TUNNEL; }
	void Travel();
	bool IsInverted() { return isInverted; };

};