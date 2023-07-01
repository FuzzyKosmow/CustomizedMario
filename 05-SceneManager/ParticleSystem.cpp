#include "ParticleSystem.h"
#include "PlayScene.h"
#include <cstdlib>
#include <random>
#include <algorithm>
using namespace std;
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



void ParticleSystem::Update (DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->IsDeleted())
		{
			particles.erase(particles.begin() + i);
			//Safe guard to make sure no funny business happens
			if (spawned >0)
				spawned--;
			continue;
		}
	}
}
//Count must be bigger than 4.
// X,y is supposed where the system will spawn. It can then be modified the center point spawn of the particle using the spawn offset
// Spawn a <count> number of particles in 4 main different direction ( Top left, top right, bottom left, bottom right). Each direction consist at least 1 particle, maximum of (count -3)
// And will be randomized from 1 -> (count -3 - spawned) for each direction.
void ParticleSystem::SpawnStaticParticle(float x, float y, int count, int spriteID)
{
	//Seed the rand
	srand(time(NULL));
	
	if (count < 4)
		return;

	int maxParticles = count - 3;

	int topLeftSpawnCount = 1;
	int topRightSpawnCount = 1;
	int remainingCount = 2;

	if (count > 4) {
		// Generate random values for each direction
		topLeftSpawnCount = rand() % (maxParticles - 1) + 1;
		topRightSpawnCount = rand() % (maxParticles - topLeftSpawnCount) + 1;
		remainingCount = maxParticles - topLeftSpawnCount - topRightSpawnCount;

		// Ensure the remaining count is within the valid range
		remainingCount = min(remainingCount, maxParticles - 1);
		remainingCount = max(remainingCount, 1);
	}


	int bottomLeftSpawnCount = rand () % remainingCount + 1;
	int bottomRightSpawnCount = maxParticles - topLeftSpawnCount - topRightSpawnCount - bottomLeftSpawnCount;


	//Top left 
	D3DXVECTOR2 direction;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	for (int i = 0;  i< topLeftSpawnCount; i++)
	{
		direction = D3DXVECTOR2(-1, -1);
		

		//Randomize the direction from 0.0 -> 2.0. Make it float
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle( x, y , direction * spawnPower , spriteID);
		
		scene ->AddObject(p);
		particles.push_back(p);
		spawned++;
	}
	//Top right
	for (int i = 0; i < topRightSpawnCount; i++)
	{
		direction = D3DXVECTOR2(1, -1);
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle(x, y, direction * spawnPower, spriteID);

		scene->AddObject(p);
		particles.push_back(p);
		spawned++;
	}
	//Bottom left
	for (int i = 0; i < bottomLeftSpawnCount; i++)
	{
		direction = D3DXVECTOR2(-1, 1);
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle(x, y, direction * spawnPower, spriteID);

		scene->AddObject(p);
		particles.push_back(p);
		spawned++;
	}
	//Bottom right
	for (int i = 0; i < bottomRightSpawnCount; i++)
	{
		direction = D3DXVECTOR2(1, 1);
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle(x, y, direction * spawnPower, spriteID);

		scene->AddObject(p);
		particles.push_back(p);
		spawned++;
	}

}

void ParticleSystem::SpawnAnimatedParticle(float x, float y, int count, int aniID)
{
	 //Seed the rand
	srand(time(NULL));

	if (count < 4)
		return;

	int maxParticles = count - 3;

	int topLeftSpawnCount = 1;
	int topRightSpawnCount = 1;
	int remainingCount = 2;
	int bottomLeftSpawnCount = rand() % remainingCount + 1;
	int bottomRightSpawnCount = maxParticles - topLeftSpawnCount - topRightSpawnCount - bottomLeftSpawnCount;
	if (count > 4) {
		// Generate random values for each direction
		topLeftSpawnCount = rand() % (maxParticles - 1) + 1;
		topRightSpawnCount = rand() % (maxParticles - topLeftSpawnCount) + 1;
		remainingCount = maxParticles - topLeftSpawnCount - topRightSpawnCount;

		// Ensure the remaining count is within the valid range
		remainingCount = min(remainingCount, maxParticles - 1);
		remainingCount = max(remainingCount, 1);
	}
	D3DXVECTOR2 direction;
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	//Top left
	for (int i = 0; i < topLeftSpawnCount; i++)
	{
		direction = D3DXVECTOR2(-1, -1);
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle(x, y, direction * spawnPower, -1, false, aniID);

		scene->AddObject(p);
		particles.push_back(p);
		spawned++;
	}
	//Top right
	for (int i = 0; i < topRightSpawnCount; i++)
	{
		direction = D3DXVECTOR2(1, -1);
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle(x, y, direction * spawnPower, -1, false, aniID);

		scene->AddObject(p);
		particles.push_back(p);
		spawned++;
	}
	//Bottom left
	
	for (int i = 0; i < bottomLeftSpawnCount; i++)
	{
		direction = D3DXVECTOR2(-1, 1);
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle(x, y, direction * spawnPower, -1, false, aniID);

		scene->AddObject(p);
		particles.push_back(p);
		spawned++;
	}
	//Bottom right
	for (int i = 0; i < bottomRightSpawnCount; i++)
	{
		direction = D3DXVECTOR2(1, 1);
		direction.x = ((rand() % 100 + 1) / 100.0f) * direction.x;
		direction.y = ((rand() % 100 + 1) / 100.0f) * direction.y;
		Particle* p = new Particle(x, y, direction * spawnPower, -1, false, aniID);

		scene->AddObject(p);
		particles.push_back(p);
		spawned++;
	}
}

LPPARTICLESYSTEM ParticleSystem::GetInstance ()
{
	
if (__instance == NULL)
		__instance = new ParticleSystem(1,1);
	return __instance;
}

LPPARTICLESYSTEM ParticleSystem::__instance = NULL;