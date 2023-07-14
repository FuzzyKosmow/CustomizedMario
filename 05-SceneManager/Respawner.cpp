#include "Respawner.h"
#include "Turtle.h"
#include "FlyingGoomba.h"
#include "FlyingTurtle.h"
#include "Goomba.h"
#include "PlayScene.h"
#define DISTANCE_TO_RESPAWN (CGame::GetInstance()->GetBackBufferWidth()/2)*1.5
Respawner* Respawner::__instance = NULL;

Respawner* Respawner::GetInstance()
{
	if (__instance == NULL) __instance = new Respawner();
	return __instance;
}

void Respawner::AddObjectToRespawn( LPGAMEOBJECT object)
{
	//Generate an id for it using the number of respawn object 
	int id = numOfObjectToRespawn;
	objectsToSpawn[id] = object;
	numOfObjectToRespawn++;
	activeObjects[id] = NULL;
	
}

void Respawner::Respawn()
{
	//Object is added to respwner at load time, so any mobs will already be on the list. 
	//Respawn is called every frame. It acts more like a spawner, if the distance X then it spawn the object by adding it to the scene, otherwise it 
	
	//Go through object to spawn list and check if they are in the scene
	for (auto& x : objectsToSpawn)
	{
		//If the object is not in the scene
		if (activeObjects[x.first] == NULL)
		{
			//Check if the object is in the distance to respawn
			float ox, oy;
			float mx, my;
			x.second->GetPosition(ox, oy);
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			 mario->GetPosition(mx, my);
			 if (abs(mx - ox) < DISTANCE_TO_RESPAWN)
			 {
				//If it is, creating a copy of the object and then add it to the scene using SpawnAnObject.

				 //This is done to avoid the object to be deleted when the scene is cleared
				 LPGAMEOBJECT object = NULL;
				 if (dynamic_cast<CTurtle*>(x.second))
				 {
					 float limitLeft, limitRight;
					 //Get from og object
					 ((CTurtle*)x.second)->GetLimit(limitLeft, limitRight);
					 object = new CTurtle(ox,oy,limitLeft,limitRight);
				 }
				 else if (dynamic_cast<CFlyingGoomba*>(x.second))
				 {
					 object = new CFlyingGoomba(ox,oy);
				 }
				 else if (dynamic_cast<CFlyingTurtle*>(x.second))
				 {
					 //This dont have limit left or right
					 object = new CFlyingTurtle(ox,oy);
					 
				 }
				 else if (dynamic_cast<CGoomba*>(x.second))
				 {
					 object = new CGoomba(ox,oy);
				 }
				
				 SpawnAnObject(object);
				 //Add it to the active object list
				 activeObjects[x.first] = object;


			}


		}
		else
		{
			float ox, oy;
			float mx, my;
			x.second->GetPosition(ox, oy);
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			mario->GetPosition(mx, my);
			if (abs(mx - ox) > DISTANCE_TO_RESPAWN)
			{
				if (!activeObjects[x.first]->IsDeleted())
				{
					activeObjects[x.first]->Delete();
					activeObjects[x.first] = NULL;
				}
				else
				{
					activeObjects[x.first] = NULL;
				}
					
				

				
			}
		}
	}

}

void Respawner::Clear()
{
	//Because they are actual created objet with alocated memory, when clearing they need to be deleted
	//Clear the object to respawn list
	for (auto& x : objectsToSpawn)
	{
		delete x.second;
	}
	objectsToSpawn.clear();
	for (auto& x : activeObjects)
	{
		if (x.second != NULL)
		{
			delete x.second;
		}
	}
	activeObjects.clear();


}

void Respawner::SpawnAnObject(LPGAMEOBJECT object)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject( object);
	
}
