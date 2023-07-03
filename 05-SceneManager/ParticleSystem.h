#pragma once
#include "GameObject.h"


//Simple particle system that allow to shoot out n particle similiar to fireworks.\
///Particle stuffs
#define PARTICLE_SPEED_Y 0.05f
#define PARTICLE_SPEED_X 0.05f

#define PARTICLE_ACCEL_X 0.0005f //Counter force
#define PARTICLE_ACCEL_Y 0.002f //Gravity

#define PARTICLE_STARTING_FORCE 0.5f
#define PARTICLE_LIVE_TIME 3000

#define LPARTICLE Particle*
#define LPPARTICLESYSTEM ParticleSystem*

//Particle system stuffs


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
		vy = startSpeedY * abs(direction.y);

		x += vx * dt;
		y += vy * dt;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (startSpeedX < 0)
			startSpeedX = 0;
		startSpeedX -= ax * dt;
		startSpeedY += ay * dt;

		if (GetTickCount64() - spawnTime > liveTime)
		{
			this->Delete();
		}

		CCollision::GetInstance()->Process(this, dt, coObjects);
	}




	void Render();
	int GetObjectType() { return OBJECT_TYPE_PARTICLE; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};

// X,y is supposed where the system will spawn. It can then use any object x,y to spawn particle as a center
// Spawn a <count> number of particles in 4 main different direction ( Top left, top right, bottom left, bottom right). Each direction consist at least 1 particle, maximum of (count -3)
// And will be randomized from 1 -> (count -3 - spawned) for each direction.
class ParticleSystem 
{
	static ParticleSystem* __instance;

	int particleCount;
	int spawned = 0;
	std::vector<Particle*> particles;
	//How much force is pushed to the particle
	float spawnPower = 1;
public:
	
	int IsColliable() { return 0; }
	int IsBlocking() { return 0; }
	int SetSpawnPower (float spawnPower) { this->spawnPower = spawnPower; }
	void SpawnStaticParticle(float x, float y, int count, int spriteID);
	void SpawnAnimatedParticle(float x , float y,int count, int aniID);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render() {  };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {  };

	static LPPARTICLESYSTEM GetInstance();
	

};