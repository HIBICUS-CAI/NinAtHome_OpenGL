#include "main.h"
#include "bg.h"
#include "texture.h"
#include "sprite.h"

unsigned int g_BGTexture;

void InitBG()
{
	g_BGTexture = LoadTexture("rom:/bg.tga");
}


void UninitBG()
{
	UnloadTexture(g_BGTexture);
}


void UpdateBG()
{

}


void DrawBG()
{
	SetTexture(g_BGTexture);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}
