#pragma once
#include "Vector2D.h"

class GameObject;
//class Vector2D;

#define PI 3.141592f
#define DEGTORAD(degree) (degree / 180) * PI 

/// <summary>
/// 2022.02.03. MG.
/// 
/// 월드 좌표만 구현한 트랜스폼
/// </summary>
class Transform
{
public:
	Transform(GameObject* object);
	~Transform();

private:
	GameObject* mGameObject;

	Vector2D mPosition;		// 위치
	Vector2D mScale;		// 스케일
	Vector2D mRotation;		// 회전 (방향벡터)

	D2D1::Matrix3x2F mWorldTransformMatrix;		// 월드 변환 매트릭스

	D2D1::Matrix3x2F mWorldTranslateMatrix;		// 월드 T 매트릭스		// 이 3개의 월드 매트릭스 변수들은 밖에서 쓸 일 없음?
	D2D1::Matrix3x2F mWorldRotateMatrix;		// 월드 R 매트릭스
	D2D1::Matrix3x2F mWorldScaleMatrix;			// 월드 S 매트릭스

public:
	GameObject* GetGameObject() { return mGameObject; }

	Vector2D GetPosition() { return mPosition; }
	void SetPosition(Vector2D position);

	Vector2D GetScale() { return mScale; }
	void SetScale(Vector2D scale);

	Vector2D GetRotation() { return mRotation; }
	void SetRotation(float angle);			// 각도값을 넣으면 각도값만큼 돌아가도록 (반시계방향)
	void SetRotation(Vector2D dirVec);

	void UpdateWorldTranslateMatrix();
	void UpdateWorldRotationMatrix();
	void UpdateWorldScaleMatrix();

	void UpdateWorldTransformMatrix();

	void Update();

	D2D1::Matrix3x2F GetWorldTransformMatrix() const { return mWorldTransformMatrix; }
};