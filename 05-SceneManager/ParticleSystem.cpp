#include "ParticleSystem.h"

void Particle::Render()
{
	if (isSprite)
	{
		
		CSprites::GetInstance()->Get(spriteID)->Draw(x, y);
	}
	else
	{
		CAnimations* s = CAnimations::GetInstance();
		s->Get(aniID)->Render(x, y);

	}
	RenderBoundingBox();
}

