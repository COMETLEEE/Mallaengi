#pragma once
#include "Collision.h"

class GameObject;

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 상속을 받으려고 했는데 상속을 받으니가 재정의자가 없다고 사용이 안됨. 찾아보자
/// 
/// => 혜성쓰의 답 : Override할 때 모든 순수 가상함수를 오버라이드 해야하며, 부모 추상 클래스 내용이 있는
/// 
/// 헤더 파일을 Include 해주어야 위의 오류가 나오지 않습니다. 이거 키보드 좋네 ..
/// </summary>
class AABBCollision : public Collision
{
public:
	AABBCollision(GameObject* object);
	~AABBCollision();

	bool CheckCollision(Collision* collision);

private:
	D2D1_SIZE_F mSize;

public:
	// Getter와 Setter를 추가합니다.
	D2D1_SIZE_F GetSize() { return mSize; }
	void SetSize(D2D1_SIZE_F value) { mSize = value; }
};