#include "Detection.h"

void SquareDetectionZone::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	CSprites* s = CSprites::GetInstance();
	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
	float l, t, r, b;
	
	GetBoundingBox(l, t, r, b);

	//Very scuffed way to handle detection but hey, it works.
	// Check if Mario is within the detection zone
	
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = static_cast<int>(r - l);
	rect.bottom = static_cast<int>(b - t);
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	float yy = y - 16 / 2 + rect.bottom / 2;
	float xx = x - 16 / 2 + rect.right / 2;
	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, alpha, rect.right - 1, rect.bottom - 1);
}

void SquareDetectionZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float l, t, r, b;
	float alpha;
	GetBoundingBox(l, t, r, b);

	//Very scuffed way to handle detection but hey, it works.
	// Check if Mario is within the detection zone
	float mx, my;

	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	scene->GetPlayer()->GetPosition(mx, my);
	if (mx >= l && mx <= r && my >= t && my <= b)
	{
		playerDetected = true;
		alpha = 0.75; // Mario is within the detection zone, set higher alpha
	}
	else
	{
		playerDetected = false;
		alpha = BBOX_ALPHA; // Mario is outside the detection zone, set default alpha
	}
}



void ObjectDetector::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}


	
