#include "Fireball.h"

void CFireball::SetDirection(bool left)
{
	if (left)
		vx *= -1;
}
void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);
}
void CFireball::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;


	// simple screen edge collision!!!
	if (vx > 0 && x > 290) {
		vx *= -1;
	}
	if (vx < 0 && x < 0)
	{
		vx *= -1;
	}

}
