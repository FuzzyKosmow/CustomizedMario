#include "HUD.h"
#include "PlayScene.h"

#define HUD_MARIO_ICON_OFFSET_X -134
#define HUD_MARIO_ICON_OFFSET_Y 6

#define HUD_WORLD_OFFSET_X -98
#define HUD_WORLD_OFFSET_Y -3.3f

#define HUD_SCORE_OFFSET_X -83
#define HUD_SCORE_OFFSET_Y 6

#define HUD_SPEED_OFFSET_X -83
#define HUD_SPEED_OFFSET_Y -3.3f
#define	HUD_SPEED_MAX_NODE	6
#define HUD_SPEED_NODE_WIDTH	10


#define HUD_TIME_OFFSET_X 12
#define HUD_TIME_OFFSET_Y 6
#define HUD_TIME_MAX_CHAR 3

#define HUD_COIN_OFFSET_X 21
#define HUD_COIN_OFFSET_Y -3.3f

#define HUD_LIVE_OFFSET_X -105
#define HUD_LIVE_OFFSET_Y 6

#define HUD_NUMBER_WIDTH	10

#define CURRENT_WORLD 1
#define WORLD_MAX_CHAR 1

#define SCORE_MAX_CHAR 7


//Render
void HUD::Render()
{
	//Render general hud zone 
	CSprites* s = CSprites::GetInstance();
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();

	int world = CURRENT_WORLD;


	//general background render
	s->Get(ID_SPRITE_HUD_GENERAL)->Draw(x, y);
	s->Get(ID_SPRITE_HUD_MARIO_ICON)->Draw(x + HUD_MARIO_ICON_OFFSET_X, y + HUD_MARIO_ICON_OFFSET_Y);
	//World
	DrawNumberAt(world, x + HUD_WORLD_OFFSET_X, y + HUD_WORLD_OFFSET_Y, WORLD_MAX_CHAR);

	if (scene->GetSceneID() != SCENE_ID_OVERWORLD)
	{
		CMario* mario = (CMario*)scene->GetPlayer();
		int coin = mario->GetCoin();
		int score;
		int live;
		int timeLeft = scene->GetSceneTimeLeftInSecond();
		float speedXRatio = mario->SpeedXRatio();
		//Speed . There are six speed node using the ratio get from mario. Last node use a different sprite. When ever a node is full, it will be rendered with a different sprite
		for (int i =0; i< HUD_SPEED_MAX_NODE; i++)
		{
			if (i < HUD_SPEED_MAX_NODE - 1)
			{
				if (speedXRatio >= (i + 1) * 1.0f / HUD_SPEED_MAX_NODE)
					s->Get(ID_SPRITE_HUD_SPEED_NORMAL_FULL)->Draw(x + HUD_SPEED_OFFSET_X + i * HUD_SPEED_NODE_WIDTH, y + HUD_SPEED_OFFSET_Y);
				else
					s->Get(ID_SPRITE_HUD_SPEED_NORMAL_EMPTY)->Draw(x + HUD_SPEED_OFFSET_X + i * HUD_SPEED_NODE_WIDTH, y + HUD_SPEED_OFFSET_Y);
			}
			else
			{
				if (speedXRatio >= (i + 1) * 1.0f / HUD_SPEED_MAX_NODE)
					s->Get(ID_SPRITE_HUD_SPEED_LAST_FULL)->Draw(x + HUD_SPEED_OFFSET_X + i * HUD_SPEED_NODE_WIDTH, y + HUD_SPEED_OFFSET_Y);
				else
					s->Get(ID_SPRITE_HUD_SPEED_LAST_EMPTY)->Draw(x + HUD_SPEED_OFFSET_X + i * HUD_SPEED_NODE_WIDTH, y + HUD_SPEED_OFFSET_Y);
			}

		}
		//Time
		DrawNumberAt(timeLeft, x + HUD_TIME_OFFSET_X, y + HUD_TIME_OFFSET_Y, HUD_TIME_MAX_CHAR);
	
		//Coin
		int coinDigits = NumberDigits(coin);
		DrawNumberAt(coin, x + HUD_COIN_OFFSET_X , y + HUD_COIN_OFFSET_Y, coinDigits);
		//Live
		live = mario->GetLive();
		int liveDigits = NumberDigits(live);
		DrawNumberAt(live , x + HUD_LIVE_OFFSET_X, y + HUD_LIVE_OFFSET_Y, liveDigits);
		//Always render 6 number for score
		score = mario->GetScore();
		DrawNumberAt (score, x + HUD_SCORE_OFFSET_X, y + HUD_SCORE_OFFSET_Y, SCORE_MAX_CHAR);

		
	}
	else
	{
		DrawNumberAt(0, x + HUD_TIME_OFFSET_X, y + HUD_TIME_OFFSET_Y, HUD_TIME_MAX_CHAR);
	}
	
}


void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	////Update position to follow camera
	//CGame* game = CGame::GetInstance();
	//float cx, cy;
	//game->GetCamPos(cx, cy);
	//this->x = cx+150;
	//this->y = cy+230;
	//Update random number from 1-10 and back to 1 again
	
}


void HUD::QuickUpdate(float x, float y)
{
	this->x = x;
	this->y = y;
	/*DrawNumberAt (CURRENT_WORLD, x + HUD_WORLD_OFFSET_X, y + HUD_WORLD_OFFSET_Y, 2);*/
	
	

}

HUD::HUD()
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(this);
	scene->SwapObjectOrderToLast(this);
}

HUD* HUD::__instance = NULL;
HUD* HUD::GetInstance() //Also add to non-intro scene if the hud is not added yet
{
	
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}

void HUD::PopUpScoreAtMario(int score)
{
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)scene->GetPlayer();
	float x, y;
	mario->AddScore(score);
	mario->GetPosition(x, y);
	PopUpScore* popUpScore = new PopUpScore(x,y,score);
	scene->AddObject(popUpScore);
	scene->SwapObjectOrderToLast(popUpScore);
	
}

void HUD::DrawNumberAt(int number, float x, float y, int maxNumOfDigit)
{
	//Draw number at x,y
	//Get the number of digits
	int numOfDigit = 0;
	int temp = number;
	while (temp > 0)
	{
		temp /= 10;
		numOfDigit++;
	}
	//Draw the number
	CSprites* sprites = CSprites::GetInstance();
	for (int i = 0; i < maxNumOfDigit; i++)
	{
		int digit = number % 10;
		sprites->Get(ID_SPRITE_HUD_NUMBER_0 + digit)->Draw(x + (maxNumOfDigit - i - 1) * HUD_NUMBER_WIDTH, y);
		number /= 10;
	}
}

//Small utils
int NumberDigits(int number)
{
	if (number == 0) return 1;
	int numOfDigit = 0;
	
	int temp = number;
	while (temp > 0)
	{
		temp /= 10;
		numOfDigit++;
	}
	
	return numOfDigit;
}

//Popup score: Use x, y to as start render location. Slowly float up and disapear after 1s
void PopUpScore::Render()
{
	
	HUD::GetInstance()->DrawNumberAt(score, x, y, scoreDigits);
	
	
}

PopUpScore::PopUpScore(float x, float y, int score)
{
	this->score = score;
	this->x = x;
	this->y = y;
	this->scoreDigits = NumberDigits(score);
	LPPLAYSCENE scene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	
	timeStart = GetTickCount64();
}

void PopUpScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Update position
	y -= HUD_POPUP_SCORE_SPEED_Y * dt;
	//Update time
	ULONGLONG now = GetTickCount64();
	if (now - timeStart > HUD_POPUP_SCORE_TIME)
	{
		this->Delete();
	}
}