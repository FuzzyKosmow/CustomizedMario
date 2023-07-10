#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"
#include "Tunnel.h"
#include "OverworldMario.h"
#include "OverworldNode.h"
void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGame* game = CGame::GetInstance();
	LPPLAYSCENE scene = (LPPLAYSCENE)game->GetCurrentScene();

	if (scene->ControlLocked())
		return;
	int sceneID = scene->GetSceneID();

	if (sceneID != INTRO_SCENE_ID && sceneID != OVERWORLD_SCENE_ID)
	{
		switch (KeyCode)
		{
		case DIK_DOWN:
			if (mario->OnTravelableTunnel())
			{
				CTunnel* tunnel = (CTunnel*)mario->GetTravelableTunnel();
				if (!tunnel->IsInverted()) //Inverted tunnnel is travelled automatically upon collision
					tunnel->Travel();
			}
			else
			{
				mario->SetState(MARIO_STATE_SIT);
			}

			break;
		case DIK_S:

			mario->SetState(MARIO_STATE_JUMP);
			if (mario->OnTravelableTunnel())
			{
				CTunnel* tunnel = (CTunnel*)mario->GetTravelableTunnel();
				if (tunnel->IsInverted()) //Inverted tunnnel is travelled automatically upon collision
					tunnel->Travel();
			}
			break;

		case DIK_A:
			//Tail attack if level raccoon
			if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
			{
				//Set mario state to tail attack
				if (mario->GetXDirection() > 0)
				{
					mario->SetState(MARIO_STATE_TAIL_ATTACK_RIGHT);
				}
				else
				{
					mario->SetState(MARIO_STATE_TAIL_ATTACK_LEFT);
				}
			}
			break;
		case DIK_1:
			mario->SetLevel(MARIO_LEVEL_SMALL);
			break;
		case DIK_2:
			mario->SetLevel(MARIO_LEVEL_BIG);
			break;
		case DIK_3:
			mario->SetLevel(MARIO_LEVEL_RACCOON);
			break;
		case DIK_0:
			mario->SetState(MARIO_STATE_DIE);
			break;
		case DIK_ESCAPE:
			CGame::GetInstance()->TogglePause();
			break;
		case DIK_L:

			CGame::GetInstance()->PauseFor(2000);
			break;
			// Pause indefinitely and unpause when pressed again
		}


		//case DIK_R: // reset
		//	/*Reload();*/
		//	break;
	}
	else if (sceneID == OVERWORLD_SCENE_ID) //Overworld controls
	{
		COverworldMario* marioO = (COverworldMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		switch (KeyCode)
		{
		case DIK_DOWN:
			marioO->Move(OverworldMovementDirection_Down);
			break;
		case DIK_UP:
			marioO->Move(OverworldMovementDirection_Up);
			break;
		case DIK_LEFT:
			marioO->Move(OverworldMovementDirection_Left);
			break;

		case DIK_RIGHT:
			marioO->Move(OverworldMovementDirection_Right);
			break;
		case DIK_S:
			if (marioO->IsOnNode())
			{
				COverworldNode* node = (COverworldNode*)marioO->GetCurrentNode();
				node->SwitchScene();
			}
			break;
		}

	}

}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (scene->ControlLocked())
		return;
	int sceneID = scene->GetSceneID();
	if (sceneID != INTRO_SCENE_ID || sceneID != OVERWORLD_SCENE_ID)
	{
		switch (KeyCode)
		{
		case DIK_S:
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
			break;
		case DIK_DOWN:
			mario->SetState(MARIO_STATE_SIT_RELEASE);
			break;
		}
	}

}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	LPPLAYSCENE scene = (LPPLAYSCENE)game->GetCurrentScene();
	int sceneID = scene->GetSceneID();
	if (scene->ControlLocked())
		return;

	if (sceneID != SCENE_ID_INTRO || sceneID != SCENE_ID_OVERWORLD)
	{
		if (!scene->ControlIsLocked())
		{
			if (mario->GetState() == MARIO_STATE_TAIL_ATTACK_LEFT || mario->GetState() == MARIO_STATE_TAIL_ATTACK_RIGHT)
			{
				//Let it do it's state thing.
				return;
			}
			if (game->IsKeyDown(DIK_RIGHT))
			{
				if (game->IsKeyDown(DIK_A))
				{
					mario->SetState(MARIO_STATE_RUNNING_RIGHT);

				}
				else
				{
					mario->SetState(MARIO_STATE_WALKING_RIGHT);
				}
			}
			else if (game->IsKeyDown(DIK_LEFT))
			{
				if (game->IsKeyDown(DIK_A))

				{
					mario->SetState(MARIO_STATE_RUNNING_LEFT);
				}
				else
				{
					mario->SetState(MARIO_STATE_WALKING_LEFT);
				}
			}
			else
			{

				mario->SetState(MARIO_STATE_IDLE);
			}
		}

	}
}