
#include "SecretBrickWithButton.h"



void CSecretBrickWithButton::SetState (int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SECRET_BRICK_WITH_BUTTON_STATE_NORMAL:
		break;
	case SECRET_BRICK_WITH_BUTTON_STATE_SHOW_BUTTON:
		break;
	}
}

void CSecretBrickWithButton::Update (DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Enter state, spawn the button 
	if (state == SECRET_BRICK_WITH_BUTTON_STATE_NORMAL && button == NULL)
	{
		button = new CGroundButton(x + SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_X, y + SECRET_BRICK_WITH_BUTTON_BUTTON_SPAWN_OFFSET_Y);

	}
	if (button != NULL)
	{
		if (button->GetPressed() && !convertedBrickToCoin)
		{
			//Turn all the coin inside the detection zone into coin

			///
			convertedBrickToCoin = true;
		}
		
	}
	
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
	}
}