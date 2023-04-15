#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(int spriteSheetIndex, Vector2D pivot, D2D1_SIZE_F size, float delayTime, Vector2D posInSheet, Vector2D spritePivot)
{
	mSpriteSheetIndex = spriteSheetIndex;
	mPivot = pivot;
	mSize = size;
	mDelayTime = delayTime;
	mPosInSheet = posInSheet;
	mSpritePivot = spritePivot;
}

Sprite::~Sprite()
{
}