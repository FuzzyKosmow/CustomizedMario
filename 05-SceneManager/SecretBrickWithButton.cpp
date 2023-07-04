#include "SecretBrickWithButton.h"


CSecretBrickWithButton::CSecretBrickWithButton(float x, float y): CBrick(x, y) {
	state = SECRET_BRICK_WITH_BUTTON_STATE_NORMAL;
	detector = new ObjectDetector(x, y, 15, 15, OBJECT_TYPE_BRICK);
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(detector);
	detector->MakeInvisible();
};

void CSecretBrickWithButton::SetState (int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SECRET_BRICK_WITH_BUTTON_STATE_NORMAL:
		break;
	case SECRET_BRICK_WITH_BUTTON_STATE_SHOW_BUTTON:
		button = new CGroundButton(x + SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_X, y + SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_Y);
		LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(button);
		break;
	}
}

void CSecretBrickWithButton::Update (DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (button != NULL)
	{
		if (button->GetPressed() && !convertedBrickToCoin)
		{
			LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			vector<LPGAMEOBJECT> objects;
			objects = detector->GetDetectedObjects ();
			if (!objects.empty())
			{
				for (size_t i = 0; i < objects.size(); i++)
				{
					float coinX;
					float coinY;
					objects[i]->GetPosition(coinX, coinY);
					objects[i]->Delete();

					bool activateCoin = true;
					CCoin* coin = new CCoin(coinX, coinY, activateCoin);
					scene->AddObject(coin);
					
					

				}
				DebugOut(L"Coin converted\n");
			}
			


			
			convertedBrickToCoin = true;
		}
		
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
	
}

void CSecretBrickWithButton::Render()
{
	int aniID = -1;
	CAnimations * ani = CAnimations::GetInstance();
	switch (state)
	{
		case SECRET_BRICK_WITH_BUTTON_STATE_NORMAL:
			aniID = SECRET_BRICK_WITH_BUTTON_ANI_NORMAL;
			break;
		case SECRET_BRICK_WITH_BUTTON_STATE_SHOW_BUTTON:
			aniID = SECRET_BRICK_WITH_BUTTON_ANI_SHOW_BUTTON;
			break;
		default :
			break;
	}
	ani->Get(aniID)->Render(x, y);
}


void CSecretBrickWithButton::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}