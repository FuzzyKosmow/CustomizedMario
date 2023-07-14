#pragma once
#include "Mushroom.h"

#define ID_ANI_GREENSHROOM_WALKING	6001
#define SCORE_GREENSHROOM			1000
class CGreenshroom : public CShroom
{
public:
	CGreenshroom(float x, float y) :CShroom(x, y) {};
	void Render()
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_GREENSHROOM_WALKING)->Render(x, y);
	}
	int GetObjectType() {
		return OBJECT_TYPE_GREENSHROOM;
	}
	
};