#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "Coin.h"


//This secret is simply a brick that turn all other coin within detectio zone into a coin


class SecretWorld1_1 : public CGameObject
{


public:
	SecretWorld1_1(float x, float y) : CGameObject(x, y) {};

};

