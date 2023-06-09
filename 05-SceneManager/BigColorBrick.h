#include "Brick.h"

#include "GameObject.h"
#include "Sprites.h"
#include "Sprite.h"
//Color definition, both in here and in txt file. WHITE = 1, GREEN = 2, PINK = 3, BLUE = 4
#define COLOR_WHITE 1
#define COLOR_GREEN 2
#define COLOR_PINK 3
#define COLOR_BLUE 4

//White brick id


#define ID_SPRITE_COLOR_BRICK_WHITE_TOP_1 91001
#define ID_SPRITE_COLOR_BRICK_WHITE_TOP_2 91002
#define ID_SPRITE_COLOR_BRICK_WHITE_TOP_3 91003

#define ID_SPRITE_COLOR_BRICK_WHITE_MIDDLE_1 91011
#define ID_SPRITE_COLOR_BRICK_WHITE_MIDDLE_2 91012
#define ID_SPRITE_COLOR_BRICK_WHITE_MIDDLE_3 91013

#define ID_SPRITE_COLOR_BRICK_WHITE_BOTTOM_1 91021
#define ID_SPRITE_COLOR_BRICK_WHITE_BOTTOM_2 91022
#define ID_SPRITE_COLOR_BRICK_WHITE_BOTTOM_3 91023

// Green brick id
#define ID_SPRITE_COLOR_BRICK_GREEN_TOP_1 92001
#define ID_SPRITE_COLOR_BRICK_GREEN_TOP_2 92002
#define ID_SPRITE_COLOR_BRICK_GREEN_TOP_3 92003

#define ID_SPRITE_COLOR_BRICK_GREEN_MIDDLE_1 92011
#define ID_SPRITE_COLOR_BRICK_GREEN_MIDDLE_2 92012
#define ID_SPRITE_COLOR_BRICK_GREEN_MIDDLE_3 92013

#define ID_SPRITE_COLOR_BRICK_GREEN_BOTTOM_1 92021
#define ID_SPRITE_COLOR_BRICK_GREEN_BOTTOM_2 92022
#define ID_SPRITE_COLOR_BRICK_GREEN_BOTTOM_3 92023

//Pink brick id
#define ID_SPRITE_COLOR_BRICK_PINK_TOP_1 93001	
#define ID_SPRITE_COLOR_BRICK_PINK_TOP_2 93002
#define ID_SPRITE_COLOR_BRICK_PINK_TOP_3	93003

#define ID_SPRITE_COLOR_BRICK_PINK_MIDDLE_1 93011
#define ID_SPRITE_COLOR_BRICK_PINK_MIDDLE_2 93012
#define ID_SPRITE_COLOR_BRICK_PINK_MIDDLE_3 93013

#define ID_SPRITE_COLOR_BRICK_PINK_BOTTOM_1 93021
#define ID_SPRITE_COLOR_BRICK_PINK_BOTTOM_2 93022
#define ID_SPRITE_COLOR_BRICK_PINK_BOTTOM_3 93023

//Blue brick id
#define ID_SPRITE_COLOR_BRICK_BLUE_TOP_1 94001
#define ID_SPRITE_COLOR_BRICK_BLUE_TOP_2 94002
#define ID_SPRITE_COLOR_BRICK_BLUE_TOP_3 94003

#define ID_SPRITE_COLOR_BRICK_BLUE_MIDDLE_1 94011
#define ID_SPRITE_COLOR_BRICK_BLUE_MIDDLE_2 94012
#define ID_SPRITE_COLOR_BRICK_BLUE_MIDDLE_3 94013

#define ID_SPRITE_COLOR_BRICK_BLUE_BOTTOM_1 94021
#define ID_SPRITE_COLOR_BRICK_BLUE_BOTTOM_2	94022
#define ID_SPRITE_COLOR_BRICK_BLUE_BOTTOM_3	94023

//Shadow id
#define ID_SPRITE_COLOR_BRICK_SHADOW_VERTICAL_1 95001
#define ID_SPRITE_COLOR_BRICK_SHADOW_VERTICAL_2 95002
//Brick height and width
#define COLOR_BRICK_HEIGHT 15
#define COLOR_BRICK_WIDTH 15

#define COLOR_BRICK_STATE_NO_HITBOX 0
#define COLOR_BRICK_STATE_HITBOX	1
class CBigColorBrick : public CGameObject
{
	int color;
	int height;  //How many small brick vertically
	int width;  // how many small brick horizontally
	int spriteIDBeginTop;
	int spriteIDMiddleTop;
	int spriteIDEndTop;

	int spriteIDBeginBottom;
	int spriteIDMiddleBottom;
	int spriteIDEndBottom;

	int spriteIDBeginMiddle;
	int spriteIDMiddleMiddle;
	int spriteIDEndMiddle;
public:
	bool blocking = false;
	
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { 
		if (blocking)
			return 1;
		else
			return 0;
	};
	void SetBlock(bool value) {
		blocking = value;
		
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	 void RenderBoundingBox();
	void SetState(int state) {

		this->state = state;

	};
	CBigColorBrick(float x, float y, int color, int width, int height) : CGameObject(x, y)
	{
		this->color = color;
		this->height = height;
		this->width = width;
		
		switch (color)
		{
		case COLOR_WHITE:
		{
			spriteIDBeginTop = ID_SPRITE_COLOR_BRICK_WHITE_TOP_1;
			spriteIDMiddleTop = ID_SPRITE_COLOR_BRICK_WHITE_TOP_2;
			spriteIDEndTop = ID_SPRITE_COLOR_BRICK_WHITE_TOP_3;

			spriteIDBeginBottom = ID_SPRITE_COLOR_BRICK_WHITE_BOTTOM_1;
			spriteIDMiddleBottom = ID_SPRITE_COLOR_BRICK_WHITE_BOTTOM_2;
			spriteIDEndBottom = ID_SPRITE_COLOR_BRICK_WHITE_BOTTOM_3;

			spriteIDBeginMiddle = ID_SPRITE_COLOR_BRICK_WHITE_MIDDLE_1;
			spriteIDMiddleMiddle = ID_SPRITE_COLOR_BRICK_WHITE_MIDDLE_2;
			spriteIDEndMiddle = ID_SPRITE_COLOR_BRICK_WHITE_MIDDLE_3;
			break;
		}
		case COLOR_GREEN:
		{
			spriteIDBeginTop = ID_SPRITE_COLOR_BRICK_GREEN_TOP_1;
			spriteIDMiddleTop = ID_SPRITE_COLOR_BRICK_GREEN_TOP_2;
			spriteIDEndTop = ID_SPRITE_COLOR_BRICK_GREEN_TOP_3;
			spriteIDBeginBottom = ID_SPRITE_COLOR_BRICK_GREEN_BOTTOM_1;
			spriteIDMiddleBottom = ID_SPRITE_COLOR_BRICK_GREEN_BOTTOM_2;
			spriteIDEndBottom = ID_SPRITE_COLOR_BRICK_GREEN_BOTTOM_3;
			spriteIDBeginMiddle = ID_SPRITE_COLOR_BRICK_GREEN_MIDDLE_1;
			spriteIDMiddleMiddle = ID_SPRITE_COLOR_BRICK_GREEN_MIDDLE_2;
			spriteIDEndMiddle = ID_SPRITE_COLOR_BRICK_GREEN_MIDDLE_3;
			break;

		}
		case COLOR_PINK:
		{
			spriteIDBeginTop = ID_SPRITE_COLOR_BRICK_PINK_TOP_1;
			spriteIDMiddleTop = ID_SPRITE_COLOR_BRICK_PINK_TOP_2;
			spriteIDEndTop = ID_SPRITE_COLOR_BRICK_PINK_TOP_3;
			spriteIDBeginBottom = ID_SPRITE_COLOR_BRICK_PINK_BOTTOM_1;
			spriteIDMiddleBottom = ID_SPRITE_COLOR_BRICK_PINK_BOTTOM_2;
			spriteIDEndBottom = ID_SPRITE_COLOR_BRICK_PINK_BOTTOM_3;
			spriteIDBeginMiddle = ID_SPRITE_COLOR_BRICK_PINK_MIDDLE_1;
			spriteIDMiddleMiddle = ID_SPRITE_COLOR_BRICK_PINK_MIDDLE_2;
			spriteIDEndMiddle = ID_SPRITE_COLOR_BRICK_PINK_MIDDLE_3;
			break;
		}
		case COLOR_BLUE:
		{
			spriteIDBeginTop = ID_SPRITE_COLOR_BRICK_BLUE_TOP_1;
			spriteIDMiddleTop = ID_SPRITE_COLOR_BRICK_BLUE_TOP_2;
			spriteIDEndTop = ID_SPRITE_COLOR_BRICK_BLUE_TOP_3;
			spriteIDBeginBottom = ID_SPRITE_COLOR_BRICK_BLUE_BOTTOM_1;
			spriteIDMiddleBottom = ID_SPRITE_COLOR_BRICK_BLUE_BOTTOM_2;
			spriteIDEndBottom = ID_SPRITE_COLOR_BRICK_BLUE_BOTTOM_3;
			spriteIDBeginMiddle = ID_SPRITE_COLOR_BRICK_BLUE_MIDDLE_1;
			spriteIDMiddleMiddle = ID_SPRITE_COLOR_BRICK_BLUE_MIDDLE_2;
			spriteIDEndMiddle = ID_SPRITE_COLOR_BRICK_BLUE_MIDDLE_3;
			break;

		}
		default:
			break;
		}
		
	}
	
	
	
	
	
};