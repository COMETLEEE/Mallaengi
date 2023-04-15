#pragma once

/// <summary>
/// 모든 버튼들의 Base Class.
/// 
/// 눌렸을 떄의 이벤트 오버라이드 함수가 있습니다.
/// 
/// 2022. 02. 11. Comet
/// </summary>
class ButtonBase : public GameObject
{
public:
	ButtonBase();
	virtual ~ButtonBase();

protected:
	// Button Size (이 친구는 Collider로 돌리지 않는다)
	D2D1_SIZE_F mSize;

	bool mIsClicked;

	// 활성화할 것인지
	bool mIsActivated;

	// 스퀘어 버튼이냐 아니면 원형 버튼이냐
	bool mIsSquare;

	bool IsCursorOnButton();

	// 피봇
	Vector2D mPivot;

public:

	D2D1_SIZE_F GetSize() { return mSize; }

	void SetSize(D2D1_SIZE_F size) { mSize = size; }

	virtual void FixedUpdate() override;

	virtual void Update() override;

	virtual void OnButtonClicked();

	void SetActivate(bool active);
};