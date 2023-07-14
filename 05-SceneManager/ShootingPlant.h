
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Collision.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Mario.h"
#include "debug.h"
#include "PlayScene.h"
#include "Detection.h"

#define PLANT_SHOW_UP_SPEED 0.3f



#define SHOOTING_PLANT_STATE_IDLE 0
#define SHOOTING_PLANT_STATE_SHOWING 1
#define SHOOTING_PLANT_STATE_SHOOTING 2
#define SHOOTING_PLANT_STATE_RETRACT 3

//Shooting plant stats
#define SHOOTING_PLANT_IDLE_TIME 1000
#define SHOOTING_PLANT_SHOW_TIME 1000
#define SHOOTING_PLANT_SHOOT_TIME 1000
#define SHOOTING_PLANT_RETRACT_TIME 1000
#define SHOOTING_PLANT_SHOW_HEIGHT_DIFFERENCE 50
#define SHOOTING_PLANT_SHOOT_INTERVAL 2000
#define SHOOTING_PLANT_BBOX_HEIGHT 32
#define SHOOTING_PLANT_BBOX_WIDTH 16
#define SHOOTING_PLANT_DETECTION_ZONE_SIZE 20

//Projectile stats
#define PLANT_PROJECTILE_SPEED 0.1f
#define PLANT_PROJECTILE_ROTATION_TIME 100
#define PLANT_PROJECTILE_BBOX_HEIGHT 10
#define PLANT_PROJECTILE_BBOX_WIDTH 10
#define PLANT_SPAWN_OFFSET 10
#define PLANT_SPAWN_OFFSET_Y_DOWN -10
#define PLANT_PROJECTILE_LIFE_TIME 3000
#define PLANT_PROJECTILE_ROTATION_DEGREE 60
#define PLANT_PROJECTILE_AX 0.000011f
#define PLANT_PROJECTILE_AY 0.00001f


//Score
#define SHOOTING_PLANT_SCORE 300

class PlantProjectile : public CGameObject {
	
	float speed = PLANT_PROJECTILE_SPEED;
	float currentRotation = 0;
	D3DXVECTOR2 direction = D3DXVECTOR2(0, 0);
	ULONGLONG spawnTime;
	ULONGLONG lastRotationTime = 0;
	//Note just spawn the thing a bit away from the plant
public:
	PlantProjectile(float x, float y, D3DXVECTOR2 direction)
	{
		this->x = x;
		this->y = y;
		this->vx =direction.x * PLANT_PROJECTILE_SPEED;
		this->vy = direction.y * PLANT_PROJECTILE_SPEED;
		
		this->direction = direction;
		spawnTime = GetTickCount64();
	}
	void Render();
	int IsCollidable() { return 0; };
	int IsBlocking() { return 0; };
	void OnNoCollision(DWORD dt);
	
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	void RenderBoundingBox();
	int GetObjectType() { return OBJECT_TYPE_PLANT_PROJECTILE; };
};



class CShootingPlant : public CGameObject {
protected:
	//Time trackers
	ULONGLONG show_start = 0;
	ULONGLONG shoot_start = 0;
	ULONGLONG retract_start = 0;
	ULONGLONG last_shot = 0;
	ULONGLONG idle_start = 0;

	float baseX; //Defalt position
	float baseY;
	int detectionZoneSize = SHOOTING_PLANT_DETECTION_ZONE_SIZE;
	//Detectionzone, only make make the plant start working when mario is in the zone
	SquareDetectionZone* dZone;
	PlantProjectile* projectile = NULL;
public:
	int IsBlocking() { return 0; };
	int IsCollidable() { return 1; }
	CShootingPlant(float x, float y) : CGameObject(x, y) {
		
		SetState(SHOOTING_PLANT_STATE_IDLE);
		dZone = new SquareDetectionZone(x, y, detectionZoneSize);
		dZone->MakeInvisible();
		baseX = x;
		baseY = y;
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(dZone);
	
	};
	void Render();
	void Update( DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	int GetObjectType () { return OBJECT_TYPE_SHOOTING_PLANT; };
};


