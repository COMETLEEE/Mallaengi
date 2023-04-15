#pragma once

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 모든 그리는 것을 담당하는 랜더러 클래스
/// </summary>
class Renderer
{
public:
	Renderer(GameObject* object);
	virtual ~Renderer();

protected:
	GameObject* mGameObject;

	// 화면에 몇 번째 순서로 출력이 될 것입니까 ..?
	int mSortOrder;

public:
	virtual void Render();
	virtual void Release() abstract;

	// SortOrder Getter / Setter
	int GetSortOrder() const { return mSortOrder; }
	void SetSortOrder(int value) { mSortOrder = value; }

	GameObject* GetGameObject() { return mGameObject; }
};