#pragma once
// #include "Vector2D.h"

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 카메라 만들어보자
/// </summary>
class Camera
{
public:
	Camera(GameObject* gameObject);
	~Camera();
	
private:
	GameObject* mGameObject;			// 카메라를 고정할 오브젝트(pos 필요)

	// 카메라 중점 위치 -> 좌상단으로 잡기
	Vector2D mLeftTop;

	// 카메라의 크기
	D2D1_SIZE_F mSize;
	//Vector2D mSize;

public:
	D2D1_SIZE_F GetSize() { return mSize; }			// 카메라의 크기 받기

	GameObject* GetGameObject() { return mGameObject; }

	void UpdateCamera();					// 카메라 업데이트 계속 해주기
};