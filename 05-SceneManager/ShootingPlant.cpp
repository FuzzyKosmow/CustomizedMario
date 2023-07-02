#pragma once
#include "ShootingPlant.h"
#include "Sprites.h"
#include "Animations.h"
#include "PlayScene.h"
#include "Sprites.h"
#include "debug.h"
//TODO: Fix the bug that make the projectile only register from below /// FIXED : because for some reason if not you update the x,y in on no collision without using vx,vy, the collision sometimes does not register. So its better 
// To just assign vx,vy, update these value and use vx vy to update x and y. Among us
//Plant
void CShootingPlant::Render()
{
	if (state == SHOOTING_PLANT_STATE_IDLE || state == SHOOTING_PLANT_STATE_RETRACT || state == SHOOTING_PLANT_STATE_SHOWING)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_PLANT_STRAIGHT_UP)->Render(x, y);
	}
	else if (state == SHOOTING_PLANT_STATE_SHOOTING)
	{
		LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
		float mx, my;
		//4 direction, choose the one closest to the player
		scene->GetPlayer()->GetPosition(mx, my);
		float dx = mx - x;
		float dy = my - y;
		CSprites* s = CSprites::GetInstance();
		//Draw based on the direction
		if (dx >= 0 && dy <= 0)
		{
			s->Get(ID_SPRITE_PLANT_LOOK_UP_RIGHT)->Draw(x, y);

		}
		else if (dx > 0 && dy > 0)
		{
			s->Get(ID_SPRITE_PLANT_LOOK_DOWN_RIGHT)->Draw(x, y);
		}
		else if (dx < 0 && dy < 0)
		{
			s->Get(ID_SPRITE_PLANT_LOOK_UP_LEFT)->Draw(x, y);
		}
		else
		{
			s->Get(ID_SPRITE_PLANT_LOOK_DOWN_LEFT)->Draw(x, y);
		}
	}
	/*RenderBoundingBox();*/
}

void CShootingPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	

	//If player go out of detection zone, reset . A way to hide things
	if (!dZone->PlayerDetected())
	{
		x = baseX;
		y = baseY;
		idle_start = 0;
		shoot_start = 0;
		show_start = 0;
		retract_start = 0;
		last_shot = 0;
		state = SHOOTING_PLANT_STATE_IDLE;


		return;
	}
	if (state == SHOOTING_PLANT_STATE_IDLE)
	{
		if (dZone->PlayerDetected() && GetTickCount64() - idle_start > SHOOTING_PLANT_IDLE_TIME)
		{
			state = SHOOTING_PLANT_STATE_SHOWING;
			show_start = GetTickCount64();
		}
		else
		{
			x = baseX;
			y = baseY;
		}


	}
	else if (state == SHOOTING_PLANT_STATE_SHOWING)
	{
		if (GetTickCount64() - show_start > SHOOTING_PLANT_SHOW_TIME)
		{
			state = SHOOTING_PLANT_STATE_SHOOTING;
			shoot_start = GetTickCount64();
		}
		else
		{
			float heightAddEachFrame = (1000.0f / MAX_FRAME_RATE) * (SHOOTING_PLANT_SHOW_HEIGHT_DIFFERENCE) / SHOOTING_PLANT_SHOW_TIME;
			y -= heightAddEachFrame;
		}
	}
	else if (state == SHOOTING_PLANT_STATE_SHOOTING)
	{
		if (GetTickCount64() - shoot_start > SHOOTING_PLANT_SHOOT_TIME)
		{
			state = SHOOTING_PLANT_STATE_RETRACT;
			retract_start = GetTickCount64();
		}
		else
		{
			if (GetTickCount64() - shoot_start > SHOOTING_PLANT_SHOOT_TIME / 2)
			{
				if (GetTickCount64() - last_shot > SHOOTING_PLANT_SHOOT_INTERVAL)
				{
					LPPLAYSCENE scene = dynamic_cast<LPPLAYSCENE>(CGame::GetInstance()->GetCurrentScene());
					last_shot = GetTickCount64();
					float mx, my;
					scene->GetPlayer()->GetPosition(mx, my);
					D3DXVECTOR2 direction = D3DXVECTOR2(mx - x, my - y);
					float xSpawn;
					float ySpawn;
					float xSpawnForDirection;
					float ySpawnForDirection;
					//Based on mario position, choose the direction to spawn the bullet, similiar to the render function of the plant
					if (direction.x >= 0 && direction.y <= 0)
					{
						xSpawnForDirection = x + PLANT_SPAWN_OFFSET;
						ySpawnForDirection = y - PLANT_SPAWN_OFFSET;
						xSpawn = x + PLANT_SPAWN_OFFSET;
						ySpawn = y - PLANT_SPAWN_OFFSET;
					}
					else if (direction.x > 0 && direction.y > 0)
					{
						xSpawnForDirection = x + PLANT_SPAWN_OFFSET;
						ySpawnForDirection = y + PLANT_SPAWN_OFFSET;
						xSpawn = x + PLANT_SPAWN_OFFSET;
						ySpawn = y + PLANT_SPAWN_OFFSET_Y_DOWN;
						
					}
					else if (direction.x < 0 && direction.y < 0)
					{
						xSpawnForDirection = x - PLANT_SPAWN_OFFSET;
						ySpawnForDirection = y - PLANT_SPAWN_OFFSET;
						xSpawn = x - PLANT_SPAWN_OFFSET;
						ySpawn = y - PLANT_SPAWN_OFFSET;
					}	
					else
					{
						xSpawnForDirection = x - PLANT_SPAWN_OFFSET;
						ySpawnForDirection = y + PLANT_SPAWN_OFFSET;
						xSpawn = x - PLANT_SPAWN_OFFSET;
						ySpawn = y + PLANT_SPAWN_OFFSET_Y_DOWN;
					}
					//Debug direction
					direction = D3DXVECTOR2(xSpawnForDirection - x, ySpawnForDirection-y);


					//Normalize direction
					D3DXVec2Normalize(&direction, &direction);
				
					LPGAMEOBJECT bullet = new PlantProjectile(xSpawn, ySpawn, direction);
					projectile = dynamic_cast<PlantProjectile*>(bullet);
					scene->AddObject(bullet);
				}
			}
		}
	}
	else if (state == SHOOTING_PLANT_STATE_RETRACT)
	{
		if (GetTickCount64() - retract_start > SHOOTING_PLANT_RETRACT_TIME)
		{
			x = baseX;
			y = baseY;
			x = baseX;
			y = baseY;

			shoot_start = 0;
			show_start = 0;
			retract_start = 0;
			last_shot = 0;
			state = SHOOTING_PLANT_STATE_IDLE;
			idle_start = GetTickCount64();
		}
		else
		{
			float heightAddEachFrame = (1000.0f / MAX_FRAME_RATE) * (SHOOTING_PLANT_SHOW_HEIGHT_DIFFERENCE) / SHOOTING_PLANT_RETRACT_TIME;
			y += heightAddEachFrame;
		}
	}
}

void CShootingPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SHOOTING_PLANT_BBOX_WIDTH / 2;
	top = y - SHOOTING_PLANT_BBOX_HEIGHT / 2;
	right = x + SHOOTING_PLANT_BBOX_WIDTH / 2;
	bottom = y + SHOOTING_PLANT_BBOX_HEIGHT / 2;

}
void CShootingPlant::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - SHOOTING_PLANT_BBOX_WIDTH / 2 + rect.right / 2;
	float yy = y - SHOOTING_PLANT_BBOX_HEIGHT / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}
//Plant projectile
void PlantProjectile::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITE_PLANT_BULLET)->Draw(x, y, currentRotation);
	RenderBoundingBox();
}


void PlantProjectile::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}



void PlantProjectile::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	
	//Check life time, if still has time ,rotate
	if (GetTickCount64() - spawnTime < PLANT_PROJECTILE_LIFE_TIME)
	{
		if (GetTickCount64() - lastRotationTime > PLANT_PROJECTILE_ROTATION_TIME)
		{
			if (currentRotation >= 360)
				currentRotation = 0;
			
			else
				currentRotation += PLANT_PROJECTILE_ROTATION_DEGREE;
			lastRotationTime = GetTickCount64();
		}
		
	}
	else
	{
		this->Delete();
	}
	
	
	
	CCollision::GetInstance()->Process(this, dt, coObjects);
};


void PlantProjectile::GetBoundingBox( float& l, float& t, float& r, float& b)
{
	
		l = x - PLANT_PROJECTILE_BBOX_WIDTH / 2;
		t = y - PLANT_PROJECTILE_BBOX_HEIGHT / 2;
		r = l + PLANT_PROJECTILE_BBOX_WIDTH;
		b = t + PLANT_PROJECTILE_BBOX_HEIGHT;
	
}


void PlantProjectile::RenderBoundingBox()
{
		D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - PLANT_PROJECTILE_BBOX_WIDTH / 2 + rect.right / 2;
	float yy = y - PLANT_PROJECTILE_BBOX_HEIGHT / 2 + rect.bottom / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}