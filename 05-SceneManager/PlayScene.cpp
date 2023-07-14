#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "BackgroundObject.h"
#include "SampleKeyEventHandler.h"
#include "LootBrick.h"
#include "Mushroom.h"
#include "BigColorBrick.h"
#include "Tunnel.h"
#include "ShootingPlant.h"
#include "Turtle.h"
#include "Leaf.h"
#include "EatingPlant.h"
#include "FlyingGoomba.h"
#include "FlyingTurtle.h"
#include "SecretBrickWithButton.h"
#include "GroundButton.h"
#include "OverworldMario.h"
#include "OverworldNode.h"
#include "OverworldBlockingObject.h"
#include "TitleScreenChoice.h"
#include "DeathBlock.h"
#include "EndLevelLoot.h"
#include "HUD.h"
#include "Greenshroom.h"
#include "Respawner.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);

}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2
#define ASSETS_SECTION_VARIABLES 3
#define MAX_SCENE_LINE 1024

#define HUD_OVERWORLD_POS_OFFSET_X 160
#define HUD_OVERWORLD_POS_OFFSET_Y 205

#define HUD_OFFSET_X 155
#define HUD_OFFSET_Y 219

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}
void CPlayScene::_ParseSection_VARIABLES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 1)
		return;
	int typeOfVariable = atoi(tokens[0].c_str());
	switch (typeOfVariable)
	{
	case VARIABLE_TYPE_CAMERA_LIMIT:
	{
		float left = (float)atof(tokens[1].c_str());
		float top = (float)atof(tokens[2].c_str());
		float right = (float)atof(tokens[3].c_str());
		float bottom = (float)atof(tokens[4].c_str());
		float sky = (float)atof(tokens[5].c_str());

		SceneCameraLimit newCamLimit = SceneCameraLimit(left, top, right, bottom, sky);
		cameraLimits.push_back(newCamLimit);

		break;
	}
	default:
		break;
	}


}
void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < static_cast<int>(tokens.size()); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO_OVERWORLD:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new COverworldMario(x, y);
		player = (COverworldMario*)obj;
		break;
	}
	case OBJECT_TYPE_MARIO:

	{
		obj = new CMario(x, y);
		player = (CMario*)obj;
		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}






	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_FLYING_GOOMBA:
	{
		obj = new CFlyingGoomba(x, y);
		break;
	}
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN:
	{
		int activate = atoi(tokens[3].c_str());
		obj = new CCoin(x, y, activate); break;
	}
	case OBJECT_TYPE_BIG_COLOR_BRICK:
	{
		int color = atoi(tokens[3].c_str());
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		obj = new CBigColorBrick(x, y, color, width, height); break;
		break;
	}

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_PASSABLE_PLATFORM:
	{
		 float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPassablePlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_BACKGROUND_ITEM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		obj = new CBackgroundObject(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_VERTICAL_OBJECT:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		if (tokens.size() >= 10)
		{
			int blocking = atoi(tokens[9].c_str());
			obj = new CVerticalObject(
				x, y,
				cell_width, cell_height, height,
				sprite_begin, sprite_middle, sprite_end,
				blocking
			);
			break;
		}
		else
		{
			obj = new CVerticalObject(
				x, y,
				cell_width, cell_height, height,
				sprite_begin, sprite_middle, sprite_end
			);
		}

		break;

	}
	case OBJECT_TYPE_DEATH_BLOCK:
	{
		if (tokens.size() >= 5)
		{
			float width = (float)atof(tokens[3].c_str());
			float height = (float)atof(tokens[4].c_str());
			obj = new DeathBlock(x, y, width, height);
			DebugOut(L"Cusom death zone\n");
		}
		else
		{
			obj = new DeathBlock(x, y);
		}
		break;
	}
	case OBJECT_TYPE_END_LEVEL_LOOT:
	{
		obj = new EndLevelLoot(x, y);
		break;
	}
	case OBJECT_TYPE_LOOT_BRICK:
	{
		//brickSpriteType != 0 ? dynamic_cast<CLootBrick*>(obj)->SetSpriteType(brickSpriteType) : dynamic_cast<CLootBrick*>(obj)->SetSpriteType(NULL);
		int brickSpriteType;
		int lootType = atoi(tokens[3].c_str());
		if (tokens.size() > 4)
		{
			brickSpriteType = atoi(tokens[4].c_str());
		}
		else
		{
			brickSpriteType = NULL;
		}

		LPGAMEOBJECT loot;
		switch (lootType)
		{
		case LOOT_TYPE_GREEN_MUSHROOM:
			loot = new CGreenshroom(x, y);
			loot->SetPosition(x - MUSHROOM_SPAWN_OFFSET, y - MUSHROOM_SPAWN_OFFSET);
			break;
		case LOOT_TYPE_MUSHROOM:
			loot = new CShroom(x, y);
			loot->SetPosition(x - MUSHROOM_SPAWN_OFFSET, y - MUSHROOM_SPAWN_OFFSET);
			break;
		case LOOT_TYPE_COIN:
			loot = new CCoin(x, y, INACTIVE);
			loot->SetPosition(x, y - COIN_SPAWN_IN_LOOT_OFFSET);
			break;
		case LOOT_TYPE_LEAF:
			loot = new CLeaf(x, y, false);
			loot->SetPosition(x - LEAF_SPAWN_OFFSET, y - LEAF_SPAWN_OFFSET);
		default:
			break;
		}

		objects.push_back(loot);

		obj = new CLootBrick(x, y, lootType);
		dynamic_cast<CLootBrick*>(obj)->SetLoot(loot);
		if (brickSpriteType != NULL)
		{
			dynamic_cast<CLootBrick*>(obj)->SetSpriteType(brickSpriteType);
		}

		break;
	}
	case OBJECT_TYPE_TUNNEL:
	{
		int color = atoi(tokens[3].c_str());

		int height = atoi(tokens[4].c_str());
		if (tokens.size() >= 12)
		{
			int usable = atoi(tokens[5].c_str());
			bool inverted = atoi(tokens[6].c_str());
			bool firstPhaseGoDown = atoi(tokens[7].c_str());
			bool secondPhaseGoDown = atoi(tokens[8].c_str());
			float xDestination = (float)atof(tokens[9].c_str());
			float yDestination = (float)atof(tokens[10].c_str());
			int cameraLimitToSwitchTo = atoi(tokens[11].c_str());
			obj = new CTunnel(x, y, color, height, usable, inverted, firstPhaseGoDown, secondPhaseGoDown, xDestination, yDestination, cameraLimitToSwitchTo);
		}
		else
		{
			obj = new CTunnel(x, y, color, height);
		}

		break;
	}
	case OBJECT_TYPE_SHOOTING_PLANT:
	{
		obj = new CShootingPlant(x, y);
		break;
	}
	case OBJECT_TYPE_EATING_PLANT:
		obj = new CEatingPlant(x, y);
		break;
	
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	case OBJECT_TYPE_TURTLE:
	{
		float limitLeft = (float)atof(tokens[3].c_str());
		float limitRight = (float)atof(tokens[4].c_str());
		obj = new CTurtle(x, y, limitLeft, limitRight);
		break;
	}
	case OBJECT_TYPE_FLYING_TURTLE:

	{
		float limitLeft = (float)atof(tokens[3].c_str());
		float limitRight = (float)atof(tokens[4].c_str());
		obj = new CFlyingTurtle(x, y);
		break;

	}
	case OBJECT_TYPE_GROUND_BUTTON:
	{
		obj = new CGroundButton(x, y);
		break;

	}
	//Secret go here
	case OBJECT_TYPE_SECRET_BRICK_WORLD_1_1:
	{
		obj = new CSecretBrickWithButton(x, y);
		break;
	}
	case OBJECT_TYPE_OVERWORLD_NODE:
	{
		int spriteID = (int)atof(tokens[3].c_str());
		int sceneID = atoi(tokens[4].c_str());


		obj = new COverworldNode(x, y, spriteID, sceneID);
		break;
	}
	case OBJECT_TYPE_OVERWORLD_BLOCKING_OBJECT:
	{
		if (tokens.size() >= 6)
		{
			int aniID = atoi(tokens[3].c_str());
			float bbwidth = (float)atoi(tokens[4].c_str());
			float bbheight = (float)atoi(tokens[5].c_str());
			obj = new COverworldBlockingObject(x, y, aniID, bbwidth, bbheight);
		}
		else
		{
			int aniID = atoi(tokens[3].c_str());
			obj = new COverworldBlockingObject(x, y, aniID);
		}

		break;
	}
	case OBJECT_TYPE_SCREEN_TITLE_CHOICE:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] Player already initialized\n");
			return;
		}
		obj = new CTitleChoice(x, y);

		player = obj;
		DebugOut(L"Object title choice created!\n");
		break;
	}
	case OBJECT_TYPE_HUD:
	{
		obj = new HUD();
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}
	if (object_type == OBJECT_TYPE_GOOMBA ||
		object_type == OBJECT_TYPE_FLYING_GOOMBA ||
		object_type == OBJECT_TYPE_TURTLE ||
		object_type == OBJECT_TYPE_FLYING_TURTLE
		)
	{
		//Add to respawner
		if (object_type != OBJECT_TYPE_HUD) //Because hud follow the camera
			obj->SetPosition(x, y);
		Respawner::GetInstance()->AddObjectToRespawn(obj);
	}
	else
	{
		// General object setup
		if (object_type != OBJECT_TYPE_HUD) //Because hud follow the camera
			obj->SetPosition(x, y);


		objects.push_back(obj);
	}
	
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;

		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[VARIABLES]") { section = ASSETS_SECTION_VARIABLES; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case ASSETS_SECTION_VARIABLES: _ParseSection_VARIABLES(line); break;
		}
	}
	if (cameraLimits.size() > 0)
		this->cameraLimit = cameraLimits[0];

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
	sceneStarted = true;
	sceneStartTime = GetTickCount64();
	DebugOut(L"Scene started at %d\n", sceneStartTime);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	if ((id != SCENE_ID_INTRO && id != SCENE_ID_OVERWORLD))
	{
		if (GetTickCount64() - sceneStartTime > MAXIMUM_SCENE_TIME)
		{
			//Since this is normal scene, get mario and set state dead, he will transfer back to overworld automatically
			CMario* mario = (CMario*)player;
			mario->SetState(MARIO_STATE_DIE);
		}

	}


	// Update camera to follow mario
	if (!cameraLocked)
	{
		float cx, cy;
		player->GetPosition(cx, cy);

		CGame* game = CGame::GetInstance();
		cx -= game->GetBackBufferWidth() / 2;


		if (cameraLimit == SceneCameraLimit().Empty())
		{
			if (cx < 0) cx = 0;
			if (cy >= 0) cy = 0;
		}
		else
		{

			CMario* mario = (CMario*)this->GetPlayer();
			if (mario != NULL)
			{
				if (cx < cameraLimit.left) cx = cameraLimit.left;
				else if (cx >= cameraLimit.right)  cx = cameraLimit.right;



				if (cy <= cameraLimit.top) cy = cameraLimit.top; //Block at the very high above
				else if (mario->IsFlying() || mario->IsDescending())
				{
					cy -= game->GetBackBufferHeight() / 2;
					//Make sure its not out of camera limit
					if (cy > cameraLimit.bottom)
						cy = cameraLimit.bottom;
				}
				else if (cy <= cameraLimit.sky) 
				{


					cy -= game->GetBackBufferHeight() / 2;

				}

				else if (cy < cameraLimit.bottom && cy > cameraLimit.sky) //Not msmooth //May be irrelevant if the different between bottom and sky is very little
				{
					float mVy, mvX;
					mario->GetSpeed(mvX, mVy);
					//if (mario->GetDropDistance() >= MARIO_DROP_DISTANCE_FOR_CAMERA ) //been dropping long enough for cam to follow
					//{
					//	//Make sure its not below bottom limit.Smoothen the camera
					//	if ((cy - game->GetBackBufferHeight() / 2) >  cameraLimit.bottom)
					//		//Get the biggest value between the bottom limit and mario's position
					//			cy = max(cameraLimit.bottom, cy - game->GetBackBufferHeight() / 2);
					//	else
					//		cy -= game->GetBackBufferHeight() / 2;
					//}
					cy -= game->GetBackBufferHeight() / 2;
					
						
				}
				else
				{ 
					
					cy = cameraLimit.bottom;
					
				}

				/*cy -= game->GetBackBufferHeight() / 2;*/
				//Debug cam limit all properties
				/*DebugOut(L" Camera limit: %f, %f, %f, %f\n", cameraLimit.left, cameraLimit.top, cameraLimit.right, cameraLimit.bottom);*/
			}
			else
			{
				if (cx < 0) cx = 0;
				if (cy >= 0) cy = 0;
			}

		}
		CGame::GetInstance()->SetCamPos(cx, cy);
		//If there is hud , set it to follow cam to reduce latency of hud
		if (GetSceneID() != SCENE_ID_INTRO)
		{
			if (!addedHud)
			{
				hud = HUD::GetInstance();
				addedHud = true;
				SwapObjectOrderToLast(hud);
			}
			if (id != SCENE_ID_OVERWORLD)
				hud->QuickUpdate(cx + HUD_OFFSET_X, cy + HUD_OFFSET_Y);
			else
				hud->QuickUpdate(cx + HUD_OVERWORLD_POS_OFFSET_X, cy + HUD_OVERWORLD_POS_OFFSET_Y);
		}


	}




	Respawner::GetInstance()->Respawn();
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < static_cast<int>(objects.size()); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{

	for (int i = 0; i < static_cast<int> (objects.size()); i++)
	{
		int OBJECT_TYPE = objects[i]->GetObjectType();
		if (OBJECT_TYPE == OBJECT_TYPE_DIMSCREEN)
		{
			CDimScreenEffect* dimScreen = dynamic_cast<CDimScreenEffect*>(objects[i]);
			if (dimScreen != NULL)
			{
				dimScreen->Unload();
			}
		}
		else if (OBJECT_TYPE == OBJECT_TYPE_HUD)
		{
			addedHud = false;
			if (hud != NULL)
			{
				hud->Unload();
				hud = NULL;
			}

		}
		else
			delete objects[i];
	}
	Respawner::GetInstance()->Clear();
	objects.clear();
	CSprites* sprites = CSprites::GetInstance();
	sprites->Clear();
	CAnimations* animations = CAnimations::GetInstance();
	animations->Clear();

	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}


void CPlayScene::AddObject(LPGAMEOBJECT obj)
{
	objects.push_back(obj);
}

void CPlayScene::SwapObjectOrderToLast(LPGAMEOBJECT obj)
{
	//Swap the object to the last of the list
	//Send the swapped object to the original obj location

	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		if (*it == obj)
		{
			objects.erase(it);
			objects.push_back(obj);
			break;
		}
	}

}