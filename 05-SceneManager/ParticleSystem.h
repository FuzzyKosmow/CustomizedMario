#pragma once
#include "GameObject.h"

#include "debug.h"
//Simple particle system that allow to shoot out n particle similiar to fireworks.\

#define PARTICLE_SPEED_Y 0.05f
#define PARTICLE_SPEED_X 0.05f
#define PARTICLE_SPEED_X_MAX 0.1f
#define PARTICLE_SPEED_Y_MAX 0.1f


#define PARTICLE_ACCEL_X 0.0005f //Counter force
#define PARTICLE_ACCEL_Y 0.002f //Gravity

#define PARTICLE_STARTING_FORCE 0.5f

#define PARTICLE_LIVE_TIME 3000
class Particle : public CGameObject
{
	float ax, ay;
	int spriteID = -1;
	int aniID = -1;
	bool isSprite = true;
	ULONGLONG liveTime = PARTICLE_LIVE_TIME;

	ULONGLONG spawnTime;

	float startSpeedX = PARTICLE_STARTING_FORCE;
	float startSpeedY = PARTICLE_STARTING_FORCE;
	D3DXVECTOR2 direction;
public:
	Particle(float x, float y, D3DXVECTOR2 direction,int spriteID = -1, bool isSprite = true, int aniID = -1) : CGameObject(x, y)
	{
		ax = PARTICLE_ACCEL_X;
		ay = PARTICLE_ACCEL_Y;
		vx = startSpeedX * direction.x;
		vy = startSpeedY * direction.y;
		this -> direction = direction;

		spawnTime = GetTickCount64();

		if (isSprite)
			this->spriteID = spriteID;
		else
			this->aniID = aniID;


	}
	void SetAccelrationX(float ax) { this->ax = ax; }
	void SetGravity(float ay) { this->ay = ay; }
	void SetSpriteID(int spriteID) { this->spriteID = spriteID; }
	void SetAniID(int aniID) { this->aniID = aniID; }
	int IsColliable() { return 0; }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt)
	{
		vx = startSpeedX * direction.x;
		vy = startSpeedY * direction.y;

		x += vx * dt;
		y += vy * dt;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (startSpeedX < 0)
			startSpeedX = 0;
		startSpeedX -= ax * dt;
		startSpeedY -= ay * dt;

		if (GetTickCount64() - spawnTime > liveTime)
		{
			this->Delete();
		}

		CCollision::GetInstance()->Process(this, dt, coObjects);
	}




	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};



//
//class ParticleSystem : public CGameObject
//{
//	int particleCount;
//	int spriteID;
//	std::list<Particle*> particles;
//};