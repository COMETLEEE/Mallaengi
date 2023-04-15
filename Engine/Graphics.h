#pragma once

class Sprite;
class Camera;

/// <summary>
/// 2022. 02. 08. MG
/// 
/// 그리는 부분에 필요한 것들
/// </summary>
class Graphics
{
private:
	//Singlton 
	Graphics();
	Graphics(const Graphics& ref) {};
	Graphics& operator=(const Graphics& ref) {};
	~Graphics();

public:
	static Graphics& GetInstance()
	{
		static Graphics instance;
		return instance;
	}

	void Initialize(HWND _hWnd);		// RenderTarget 등을 초기화

	void	CalculateLayout();
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();

	HRESULT ChangeRenderTarget();			// 명령을 수행할 메모리 영역 생성

	void BeginRender();
	void EndRender();
	void Resize();

	void DrawLine(Vector2D start, Vector2D end, D2D1_COLOR_F color);
	void DrawEllipse(Vector2D pos, int radiusX, int radiusY, D2D1_COLOR_F color);
	void DrawRectangle(int x, int y, int x1, int y1, D2D1_COLOR_F color);
	void DrawRectangle(Vector2D center, D2D1_SIZE_F size, D2D1_COLOR_F color);

	// 화면에 문자를 출력
	bool DrawText(int x, int y, const char* pch, ...);			/// 플레이어 오브젝트랑 같이 움직임. 텍스트 오브젝트를 만들어서 SetTransform 으로 위치값을 지정해줘야 할듯. Y 값은 움직이지 않도록 고정 필요.

	/// TRS 관련
	void SetTransform(const D2D1_MATRIX_3X2_F& transformMatrix);
	void SetTransformForUI(const D2D1_MATRIX_3X2_F& transformMatrix);

	/// 스프라이트 관련
	HRESULT LoadBitmapFromFile(ID2D1RenderTarget* _renderTarget, IWICImagingFactory* _WICFactory, UINT _destWidth, UINT _destHeight,
		const wchar_t* filePath, ID2D1Bitmap** _bitmap);
	void LoadSpriteSheet(const wchar_t* filePath);			// 시트 한장 로드
	void LoadSpriteSheet(INT imageID, std::string filePath);
	Sprite* LoadSpriteFromData(int spriteSheetIndex, Vector2D pivot, D2D1_SIZE_F size, float delayTime, Vector2D posInSheet);		// 로드한 시트의 정보 삽입
	void DrawSprite(Sprite* sprite, Vector2D position, float opacity = 1.f);		// 스프라이트 그리기

	Vector2D GetPivotAppliedPosition(Sprite* sprite, Vector2D pos);		// 스프라이트의 피봇을 적용한 출력 시작위치(스프라이트 좌상단) 을 반환			// 그림그릴 지점 구하기

	// 스프라이트 시트를 담을 벡터들
	std::vector<ID2D1Bitmap*> mSpriteSheets;

	// LoadJson 파일로 부른 비트맵들을 담을 맵. Draw할 때 ID로 불러올 수 있다.
	std::map<INT, ID2D1Bitmap*> mSprites;
private:
	HWND mHwnd;

	ID2D1Factory* mpFactory;
	ID2D1HwndRenderTarget* mpRenderTarget;

	ID2D1SolidColorBrush* mpBrush;
	ID2D1SolidColorBrush* mpBrush_Yellow;
	ID2D1SolidColorBrush* mpBrush_Black;

	ID2D1SolidColorBrush* mpTempBrush;		// 그리기 함수 내에서만 사용의 용도
	ID2D1SolidColorBrush* mpNowBrush;			// 바꿔가면서 여러 번 재사용의 용도

	D2D1_ELLIPSE            mEllipse;
	D2D1_RECT_F				mRectangle;

	IDWriteFactory* mpDWriteFactory;
	IDWriteTextFormat* mpTextFormat;

	/// Sprite 
	IWICImagingFactory* mpWICFactory;

	/// Camera를 쓰기위한
	Camera* mCamera;

	/// Camera를 쓰기 위한 함수
public:
	void SetCamera(Camera* camera) { mCamera = camera; }

public:
	HWND GetHandleWindow() { return mHwnd; }		// hWnd 를 받을 함수. 필요??
	D2D1_SIZE_F GetScreenSize() { return mpRenderTarget->GetSize(); }
};