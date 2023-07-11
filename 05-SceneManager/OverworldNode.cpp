#include "OverworldNode.h"
#include "OverworldMario.h"
COverworldNode::COverworldNode(float x, float y, int spriteID, int sceneIDToLoad) : CGameObject(x, y)
{
	this->sceneIdToLoad = sceneIDToLoad;
	this->spriteID = spriteID;
	marioDetector = new ObjectDetector( x, y, 1,1, OBJECT_TYPE_MARIO_OVERWORLD);
	CGame* game = CGame::GetInstance();
	LPPLAYSCENE scene  = (LPPLAYSCENE)game->GetCurrentScene();
	scene->AddObject(marioDetector);
}

void COverworldNode::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (sceneIdToLoad != -1)
	{
		if (marioDetector->ObjectDetected())
		{
			CGame* game = CGame::GetInstance();
			LPSCENE scene = game->GetCurrentScene();
			COverworldMario* mario = (COverworldMario*)((CPlayScene*)scene)->GetPlayer();
			mario->SetOnNode(this);
			hasJustSetNode = true;
		}
		else
		{
			if (hasJustSetNode)
			{
				CGame* game = CGame::GetInstance();
				LPSCENE scene = game->GetCurrentScene();
				COverworldMario* mario = (COverworldMario*)((CPlayScene*)scene)->GetPlayer();
				mario->SetOnNode(NULL);
				hasJustSetNode = false;
			}
		}
	}
	
}

void COverworldNode::Render()
{
	if (spriteID == -1)
		return;

	CSprites * sprites = CSprites::GetInstance();
	sprites->Get(spriteID)->Draw(x, y);
}


void COverworldNode::SwitchScene()
{
	CGame* game = CGame::GetInstance();
	game->InitiateSwitchScene (sceneIdToLoad);
}