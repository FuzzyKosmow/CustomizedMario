#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <unordered_map>
#include <string>
using namespace std;

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "Texture.h"
#include "KeyEventHandler.h"
#include "Scene.h"

#define MAX_FRAME_RATE 100
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

#define MARIO_START_LIVES 4
#define MARIO_MAX_ITEMS 3
/*
	Our simple game framework
*/
class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state

	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	HINSTANCE hInstance;

	ID3D10SamplerState* pPointSamplerState;

	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	int next_scene = -1;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

	
	//Pause 
	
	bool isPaused = false;
	bool isPausedIndefinitely = false; // Indicates if the game is paused indefinitely
	ULONGLONG pauseStartTime = 0;
	ULONGLONG pauseEndTime = 0;
	ULONGLONG pauseDuration = 0;
	bool pauseForTriggered = false;

	//Mario stats for loading and updating
	int marioLives = MARIO_START_LIVES;
	int marioScore = 0;
	int marioCoins = 0;
	vector<int> marioItems = vector<int>(MARIO_MAX_ITEMS, 0);


public:
	//Pause section
	bool PauseForActivated() { return pauseForTriggered; }
	void DeactivatePauseFor() { pauseForTriggered = false; pauseEndTime = GetTickCount64(); }
	void TogglePause();
	void PauseFor(ULONGLONG milliseconds);

	bool IsPausedIndefinitely() { return isPausedIndefinitely; }
	
	bool IsPaused() { return isPaused; }

	//Mostly for automatic unpause
	ULONGLONG GetPauseStartTime() { return pauseStartTime; }
	ULONGLONG GetPauseEndTime() { return pauseEndTime; }
	ULONGLONG GetPauseDuration() {

		return pauseDuration;
	}
	///
	void UpdateMarioStats(int liveLeft , int score, int coins) {
		marioLives = liveLeft;
		marioScore = score;
		marioCoins = coins;
	}
	void UpdateItems ( vector<int> items) {
		for (int i = 0; i < MARIO_MAX_ITEMS; i++) {
			marioItems[i] = items[i];
		}
	}
	
	void GetItems (vector<int>& items) {
		for (int i = 0; i < MARIO_MAX_ITEMS; i++) {
			items[i] = marioItems[i];
		}
	}
	void GetMarioStats(int& liveLeft, int& score, int& coins) {
		liveLeft = marioLives;
		score = marioScore;
		coins = marioCoins;
	}


	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen. (x,y) is at the CENTER of the image
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect, alpha, sprite_width, sprite_height);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath);
	void Pause() {
		isPaused = true;
		pauseStartTime = GetTickCount64();
	}
	
	
	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }


	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }

	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }

	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	static CGame* GetInstance();

	void SetPointSamplerState();

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }

	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void Load(LPCWSTR gameFile);
	void SwitchScene();
	void InitiateSwitchScene(int scene_id);

	void _ParseSection_TEXTURES(string line);
	int GetNextScene() { return next_scene; }

	~CGame();
};
typedef CGame* LPGAME;

