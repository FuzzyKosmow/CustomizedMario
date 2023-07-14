#pragma once
#include <unordered_map>
#include <vector>
#include "GameObject.h"

class Respawner {
private:
    static Respawner* __instance;
    std::unordered_map<int, LPGAMEOBJECT> objectsToSpawn; // Objects to be spawned with their IDs
    std::unordered_map<int, LPGAMEOBJECT> activeObjects; // Objects currently in the scene
    int numOfObjectToRespawn = 0;
    Respawner() {}

public:
    static Respawner* GetInstance();
    void AddObjectToRespawn(LPGAMEOBJECT object);
    void Respawn();
    void Clear();
    void SpawnAnObject(LPGAMEOBJECT object);
};