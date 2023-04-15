#pragma once

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 스프라이트 랜더러
/// </summary>
class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer(GameObject* gameObject);
	virtual ~SpriteRenderer();

private:
	Sprite* mSprite;			// 출력할 스프라이트 변수

	float mOpacity;				// 투명도

public:
	// 그림 그릴 스프라이트의 정보를 넣어주는 함수
	void SetSprite(Sprite* sprite);
	Sprite* GetSprite() { return mSprite; }

	float GetOpacity() { return mOpacity; }

	void SetOpacity(float opacity) { mOpacity = opacity; }

	virtual void Render() override;
	virtual void Release() override;
};