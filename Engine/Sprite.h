#pragma once

/// <summary>
/// 2022. 02. 07. MG
/// 
/// 스프라이트 정보
/// </summary>
class Sprite
{
public:
	Sprite(int spriteSheetIndex, Vector2D pivot, D2D1_SIZE_F size, float delayTime, Vector2D posInSheet, Vector2D spritePivot = {});
	~Sprite();

	int mSpriteSheetIndex;		// 해당 스프라이트가 있는 스프라이트 시트의 인덱스

	Vector2D mPivot;			// 스프라이츠 출력 중심점

	D2D1_SIZE_F mSize;			// 스프라이트 사이즈

	float mDelayTime;			// 애니메이션 재생할 때 시간 관련

	Vector2D mPosInSheet;		// 스프라이트 시트 내의 위치

	Vector2D mSpritePivot;		// 스프라이트의 피봇
};