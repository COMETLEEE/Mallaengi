#pragma once
// Collision은 충돌 체크 기능만 넣는다 ..!

class GameObject;

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 충돌 체크를 위한 충돌 베이스 클래스
/// </summary>
class Collision
{
public:
	Collision(GameObject* object);
	~Collision();

private:
	GameObject* mGameObject;

	bool mIsCollision;																// 충돌 했?안했?

	std::vector<GameObject*> mCollisionInfo;										// 충돌 정보를 담을 벡터

public:
	/// 상속을 할 때는 레퍼런스 안된다. 다형적으로 되지 않는다!
	virtual bool CheckCollision(Collision* collision) = 0;							// 충돌 했는지 안했는지 체크

	GameObject* GetGameObject() { return mGameObject; }

	bool GetIsCollision() { return mIsCollision; }
	void SetIsCollision(bool value) { mIsCollision = value; }						// 충돌 값 변경

	std::vector<GameObject*>& GetCollisionInfo() { return mCollisionInfo; }			// 값 사용하게 Get -> &(참조) 를 사용하면 편하게 값을 사용하고 지우기 가능
	void AddCollisionInfo(GameObject* object) { mCollisionInfo.push_back(object); } // 충돌정보 받기
};