#include "pch.h"
#include "Transform.h"

Transform::Transform(GameObject* object)
	: mGameObject(object),
	mPosition(Vector2D(0.f, 0.f)),
	mRotation(Vector2D(1.f, 0.f)),
	mScale(Vector2D(1.f, 1.f))
{
	UpdateWorldTranslateMatrix();
	UpdateWorldRotationMatrix();
	UpdateWorldScaleMatrix();
}

Transform::~Transform()
{

}

void Transform::SetPosition(Vector2D position)
{
	// 값을 넣어서 변경
	mPosition = position;

	UpdateWorldTranslateMatrix();
}

void Transform::SetScale(Vector2D scale)
{
	mScale = scale;

	UpdateWorldScaleMatrix();
}

void Transform::SetRotation(float angle)
{
	// 호도법 계산 (앵글 변환)
	float rad = DEGTORAD(angle);

	// 좌표 돌려
	float newX = mRotation.GetX() * cos(rad) + mRotation.GetY() * sin(rad);
	float newY = -mRotation.GetX() * sin(rad) + mRotation.GetY() * cos(rad);

	// 돌린 좌표값(벡터) 크기 -> 1로 바꾼 후 값넣기
	mRotation = Vector2D(newX, newY).Normalize();

	// 바뀐 방향벡터로 초기화
	UpdateWorldRotationMatrix();
}

void Transform::SetRotation(Vector2D dirVec)
{
	mRotation = dirVec;

	UpdateWorldRotationMatrix();
}

void Transform::UpdateWorldTranslateMatrix()
{
	// 단위행렬 만들기
	mWorldTranslateMatrix = D2D1::Matrix3x2F::Identity();

	// x, y 좌표만큼 이동
	mWorldTranslateMatrix.dx = mPosition.GetX();
	mWorldTranslateMatrix.dy = mPosition.GetY();

	// 월드좌표에 바뀐행렬값 대입
	UpdateWorldTransformMatrix();
}

void Transform::UpdateWorldRotationMatrix()
{
	// 단위행렬 만들기
	mWorldRotateMatrix = D2D1::Matrix3x2F::Identity();

	mWorldRotateMatrix._11 = mRotation.GetX();
	mWorldRotateMatrix._12 = mRotation.GetY();
	mWorldRotateMatrix._21 = -mRotation.GetY();
	mWorldRotateMatrix._22 = mRotation.GetX();

	// 월드좌표에 바뀐행렬값 대입
	UpdateWorldTransformMatrix();
}

void Transform::UpdateWorldScaleMatrix()
{
	// 단위행렬 만들기
	mWorldScaleMatrix = D2D1::Matrix3x2F::Identity();

	mWorldScaleMatrix._11 = mScale.GetX();
	mWorldScaleMatrix._22 = mScale.GetY();

	// 월드좌표에 바뀐 행렬값 대입
	UpdateWorldTransformMatrix();
}

void Transform::UpdateWorldTransformMatrix()
{
	mWorldTransformMatrix = mWorldScaleMatrix * mWorldRotateMatrix * mWorldTranslateMatrix;
}