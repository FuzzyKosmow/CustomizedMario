#include "BackgroundObject.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"
void CBackgroundObject::Render()
{
	
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteId)->Draw(x, y);
}


	