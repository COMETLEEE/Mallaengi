#pragma once

/// <summary>
/// 사각형 렌더러
/// 
/// 2022. 02.07. MG
/// </summary>
class RectRenderer : public Renderer
{
public:
	RectRenderer(GameObject* object);
	virtual ~RectRenderer();

private:
	D2D1_SIZE_F mSize;

public:
	virtual void Render() override;
	virtual void Release() override;

	D2D1_SIZE_F GetSize() { return mSize; }
	void SetSize(D2D1_SIZE_F size) { mSize = size; }
};