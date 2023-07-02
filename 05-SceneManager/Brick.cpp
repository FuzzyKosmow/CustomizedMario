#include "Brick.h"



void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::Break()
{
	DebugOut(L"Brick break\n");
	ParticleSystem *ps = ParticleSystem::GetInstance();
	ps->SpawnStaticParticle(x, y, BRICK_PARTICLE_SPAWN_COUNT, ID_SPRITE_BRICK_BREAK_PARTICLE);
	this->Delete();
}

