#include "pch.h"
#include "Graphics.h"
#include "Sprite.h"
#include "MGMath.h"

#define CAMERA_ZOOM 0.7f

Graphics::Graphics()
	: mHwnd(nullptr),
	mpFactory(nullptr),
	mpRenderTarget(nullptr),
	mpBrush(nullptr),
	mpBrush_Yellow(nullptr),
	mpBrush_Black(nullptr),
	mpTempBrush(nullptr),
	mpNowBrush(nullptr),
	mpDWriteFactory(nullptr),
	mpTextFormat(nullptr),
	mEllipse(),
	mRectangle(),
	mpWICFactory(nullptr)
{
}

Graphics::~Graphics()
{
	SafeRelease(&mpFactory);
	SafeRelease(&mpRenderTarget);
	SafeRelease(&mpBrush_Yellow);
	SafeRelease(&mpBrush_Black);
	SafeRelease(&mpDWriteFactory);
	SafeRelease(&mpTextFormat);
	SafeRelease(&mpWICFactory);
}

void Graphics::Initialize(HWND _hWnd)
{
	HRESULT hr = E_FAIL;

	mHwnd = _hWnd;

	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 20;

	// D2D Factory 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mpFactory);


	//DWrite 팩토리 생성
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory
		(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(mpDWriteFactory),
			reinterpret_cast<IUnknown**>(&mpDWriteFactory)
		);
	}

	// TextFormat 객체 생성
	if (SUCCEEDED(hr))
	{
		hr = mpDWriteFactory->CreateTextFormat
		(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"",
			&mpTextFormat
		);
	}

	if (SUCCEEDED(hr))
	{
		mpTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		mpTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}

	hr = CreateGraphicsResources();

	// 스프라이트 하기 위해 해줘야 함
	hr = CoInitialize(NULL);

	/// Sprite를 위한 팩토리 생성
	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&mpWICFactory)
			//IID_IWICImagingFactory,
			//reinterpret_cast<void**>(&pWICFactory)
		);
	}

	assert(hr == S_OK);
}

void Graphics::CalculateLayout()
{
	if (mpRenderTarget != NULL)
	{
		D2D1_SIZE_F size = mpRenderTarget->GetSize();
		const float x = size.width / 2;
		const float y = size.height / 2;
		const float radius = min(x, y);
		mEllipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	}
}

HRESULT Graphics::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (mpRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(mHwnd, &rc);

		D2D1_SIZE_U _size = D2D1::SizeU(rc.right, rc.bottom);

		hr = mpFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(mHwnd, _size),
			&mpRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color_Yellow = D2D1::ColorF(1.0f, 1.0f, 0);
			hr = mpRenderTarget->CreateSolidColorBrush(color_Yellow, &mpBrush_Yellow);

			const D2D1_COLOR_F color_Black = D2D1::ColorF(0, 0, 0);
			hr = mpRenderTarget->CreateSolidColorBrush(color_Black, &mpBrush_Black);


			hr = mpRenderTarget->CreateSolidColorBrush(color_Black, &mpBrush);

			if (SUCCEEDED(hr))
			{
				CalculateLayout();
			}
		}
	}
	return hr;
}

void Graphics::DiscardGraphicsResources()
{
	SafeRelease(&mpRenderTarget);
	SafeRelease(&mpBrush_Yellow);
	SafeRelease(&mpBrush_Black);
}

HRESULT Graphics::ChangeRenderTarget()
{
	HRESULT hr = E_FAIL;

	// 윈도우 클라이언트 영역 얻기
	RECT rc;
	GetClientRect(mHwnd, &rc);

	// 윈도우 클라이언트 영역의 크기 구하기
	D2D1_SIZE_U windowSize = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	SafeRelease(&mpRenderTarget);

	// 클라이언트 영역만큼 렌더타겟 생성
	// 인자 1번 - 화면에 대한 정보 설정, 2	번 - 하드웨어 가속받는 렌더링에대한 옵션 설정, 3번 - api 호출 성공 시 리턴되는 렌더타겟의 포인터 저장할 변수
	hr = mpFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(mHwnd, windowSize),
		&mpRenderTarget);


	return hr;
}

void Graphics::BeginRender()
{
	RECT rc;

	GetClientRect(mHwnd, &rc);

	mpRenderTarget->Resize(D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top));

	if (!(mpRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		// WM_PAINT BeginPaint()

		mpRenderTarget->BeginDraw();
		mpRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
}

void Graphics::EndRender()
{
	HRESULT hr = mpRenderTarget->EndDraw();

	// assert(hr == S_OK);
}

void Graphics::Resize()
{
	if (mpRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(mHwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		mpRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(mHwnd, NULL, FALSE);
	}
}

void Graphics::DrawLine(Vector2D start, Vector2D end, D2D1_COLOR_F color)
{
	HRESULT hr = S_OK;

	D2D1_POINT_2F startPoint;
	D2D1_POINT_2F endPoint;

	startPoint.x = start.GetX();
	startPoint.y = start.GetY();

	endPoint.x = end.GetX();
	endPoint.y = end.GetY();

	mpBrush->SetColor(color);


	if (SUCCEEDED(hr))
	{
		mpRenderTarget->DrawLine(startPoint, endPoint, mpBrush);
	}
}

void Graphics::DrawEllipse(Vector2D pos, int radiusX, int radiusY, D2D1_COLOR_F color)
{
	HRESULT hr = S_OK;

	D2D1_POINT_2F pointPos;

	pointPos.x = pos.GetX();
	pointPos.y = pos.GetY();

	mpBrush->SetColor(color);

	if (SUCCEEDED(hr))
	{
		mpRenderTarget->DrawEllipse(D2D1::Ellipse(pointPos, radiusX, radiusY), mpBrush, 2.0f, NULL);
	}
}

void Graphics::DrawRectangle(int x, int y, int x1, int y1, D2D1_COLOR_F color)
{
	D2D1_RECT_F rt;
	rt.left = (float)x;
	rt.top = (float)y;
	rt.right = (float)x1;
	rt.bottom = (float)y1;

	HRESULT hr = S_OK;

	mpBrush->SetColor(color);

	if (SUCCEEDED(hr))
	{
		mpRenderTarget->DrawRectangle(rt, mpBrush, 2.0f);
	}
}

void Graphics::DrawRectangle(Vector2D center, D2D1_SIZE_F size, D2D1_COLOR_F color)
{
	D2D1_RECT_F rt;

	rt.left = center.GetX() - (size.width / 2);
	rt.top = center.GetY() - (size.height / 2);
	rt.right = center.GetX() + (size.width / 2);
	rt.bottom = center.GetY() + (size.height / 2);

	HRESULT hr = S_OK;

	mpBrush->SetColor(color);

	if (SUCCEEDED(hr))
	{
		mpRenderTarget->DrawRectangle(rt, mpBrush, 2.0f);
	}
}

bool Graphics::DrawText(int x, int y, const char* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, lstrlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// SetTransform 으로 위치값을 설정
		//mpRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		// 폰트별 차지하는 영역 계산 필요
		mpRenderTarget->DrawText(
			unicodestr,
			wcslen(unicodestr), 
			mpTextFormat,
			//D2D1::RectF(x, y, mRenderTargetSize.width, mRenderTargetSize.height),
			D2D1::RectF((float)x, (float)y, (float)(x + 80), (float)(y + 77)),			// 뭔가 수정이 필요한데 뭔지 모르겠다 아직
			mpBrush_Yellow);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}

void Graphics::SetTransform(const D2D1_MATRIX_3X2_F& transformMatrix)
{
	// 맵의 중심으로 이동 후
	// 스케일
	// 다시 원점으로 이동
	// D2D1_MATRIX_3X2_F tm = transformMatrix;
	D2D1_SIZE_F size = mCamera->GetSize();

	D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Identity();

	Vector2D scale = mCamera->GetGameObject()->GetTransform()->GetScale();

	matrix._11 = scale.mX;
	matrix._22 = scale.mY;

	D2D1_MATRIX_3X2_F TM = transformMatrix;

	D2D1::Matrix3x2F cameraTM = mCamera->GetGameObject()->GetTransform()->GetWorldTransformMatrix();

	TM.dx = size.width / 2 + TM.dx - cameraTM.dx;
	TM.dy = size.height / 2 + TM.dy - cameraTM.dy;

	D2D1_MATRIX_3X2_F finalMat = TM * matrix;

	float absX = size.width / 2 - finalMat.dx;
	float absY = size.height / 2 - finalMat.dy;

	D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Identity();

	// 렌더 타겟을 옮기는데 .. 해상도에 맞게 ..
	trans.dx = size.width / 2 - (size.width / 2) * CAMERA_ZOOM;
	trans.dy = size.height / 2 - (size.height / 2) * CAMERA_ZOOM;

	mpRenderTarget->SetTransform(finalMat * trans);
}

void Graphics::SetTransformForUI(const D2D1_MATRIX_3X2_F& transformMatrix)
{
	D2D1_MATRIX_3X2_F mat = D2D1::Matrix3x2F::Identity();

	// 카메라 줌 비율 (무한 하드코딩)
	mat.m11 = CAMERA_ZOOM;

	mat.m22 = CAMERA_ZOOM;

	mpRenderTarget->SetTransform(mat * transformMatrix);
}

HRESULT Graphics::LoadBitmapFromFile(ID2D1RenderTarget* _renderTarget, IWICImagingFactory* _WICFactory, UINT _destWidth, UINT _destHeight, const wchar_t* filePath, ID2D1Bitmap** _bitmap)
{
	HRESULT hr = S_OK;

	// 예를 들어, PNG 파일은 압축이 되어있는 형식이기 때문에 비트맵 형식으로 압축을 해제하는 디코더를 만든다.
	IWICBitmapDecoder* pDecoder = NULL;
	// 한 파일에 여러개의 그림이 있을 수 있기 때문에 어떤 그림을 사용할지 선택한다. 
	IWICBitmapFrameDecode* pSource = NULL;
	// IWICBitmap 형식의 비트맵을 ID2D1Bitmap 형식으로 변환하기 위한 컨버터
	IWICFormatConverter* pConverter = NULL;
	// 인자로 받은 Width, Height를 비교해 비트맵의 스케일을 조정하기 위함.
	IWICBitmapScaler* pScaler = NULL;

	// 파일 경로를 읽어 디코더를 만듬.
	hr = _WICFactory->CreateDecoderFromFilename(
		filePath,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// 파일을 구성하는 이미지 중에서 첫 번째 이미지를 선택한다.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// ID2D1Bitmap으로 변환해줄 컨버터를 만든다.
		hr = _WICFactory->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		// 인자로 들어온 _destWidth, _destHeight를 비교하여 비트맵의 이미지 가로, 세로를 조절한다.
		if (_destWidth != 0 || _destHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				// 하나만 0으로 인자가 들어온 경우 이미지 자동으로 0으로 들어온 부분에 대하여 이미지 가로, 세로 비율을 맞춰서 잘라준다.
				if (_destWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destHeight) / static_cast<FLOAT>(originalHeight);
					_destWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (_destHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destWidth) / static_cast<FLOAT>(originalWidth);
					_destHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				// 스케일러 만듬.
				hr = _WICFactory->CreateBitmapScaler(&pScaler);

				if (SUCCEEDED(hr))
				{
					// 이미지를 조절한다.
					hr = pScaler->Initialize(
						pSource,
						_destWidth,
						_destHeight,
						WICBitmapInterpolationModeCubic
					);
				}

				if (SUCCEEDED(hr))
				{
					// 이미지를 변환할 준비를 한다.
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else
		{
			// 둘 다 0으로 들어오면 이미지 크기 그대로 변활할 준비를 한다.
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}

	if (SUCCEEDED(hr))
	{
		// IWICBitmap 형식의 이미지를 ID2D1Bitmap 객체로 변환하여 생성한다.
		hr = _renderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			_bitmap
		);
	}

	// 로드할 때 사용한 친구들을 릴리즈한다.
	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	// 성공 여부를 반환한다.
	return hr;
}

void Graphics::LoadSpriteSheet(const wchar_t* filePath)
{
	HRESULT _hr = S_OK;
	ID2D1Bitmap* _newSheet = nullptr;

	// 파일 경로를 읽어 비트맵을 불러온다.
	_hr = LoadBitmapFromFile(
		mpRenderTarget,
		mpWICFactory,
		0, 0,
		filePath, &_newSheet
	);

	// 성공했다면 스프라이트 시트를 모아놓은 벡터에 저장
	if (SUCCEEDED(_hr))
		mSpriteSheets.push_back(_newSheet);
}

// imageID로 분류될 수 있는 맵에 넣는 것 ..!
void Graphics::LoadSpriteSheet(INT imageID, std::string filePath)
{
	HRESULT _hr = S_OK;
	ID2D1Bitmap* _newSheet = nullptr;

	std::wstring name = std::wstring(filePath.begin(), filePath.end());

	_hr = LoadBitmapFromFile(
		mpRenderTarget,
		mpWICFactory,
		0, 0,
		name.c_str(), &_newSheet);

	// imageID로 분류될 수 있는 것 ..!
	if (SUCCEEDED(_hr))
		mSprites.emplace(imageID, _newSheet);
}

Sprite* Graphics::LoadSpriteFromData(int spriteSheetIndex, Vector2D pivot, D2D1_SIZE_F size, float delayTime, Vector2D posInSheet)
{
	return new Sprite(spriteSheetIndex, pivot, size, delayTime, posInSheet);
}

void Graphics::DrawSprite(Sprite* sprite, Vector2D position, float opacity)
{
	// 정보를 담은
	ID2D1Bitmap* sheetSprite;

	// 10000 이하는 그냥 vector에서 애니메이션 용으로 사용
	if (sprite->mSpriteSheetIndex < 5000)
		sheetSprite = mSpriteSheets.at(sprite->mSpriteSheetIndex);
	// 10000 이상은 map ID로 사용
	else
		sheetSprite = mSprites.at(sprite->mSpriteSheetIndex);

	Vector2D printLeftTop = GetPivotAppliedPosition(sprite, position) - sprite->mSpritePivot;

	mpRenderTarget->DrawBitmap(sheetSprite,
		// 화면에 그릴 좌표 (월드 포지션)
		D2D1::RectF(printLeftTop.GetX(), printLeftTop.GetY(),
			printLeftTop.GetX() + sprite->mSize.width, printLeftTop.GetY() + sprite->mSize.height),
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
		// 스프라이트 시트에서 뜯어다 쓸 하나의 스프라이트의 좌표
		D2D1::RectF(sprite->mPosInSheet.GetX(), sprite->mPosInSheet.GetY(),
			sprite->mPosInSheet.GetX() + sprite->mSize.width, sprite->mPosInSheet.GetY() + sprite->mSize.height));
}

Vector2D Graphics::GetPivotAppliedPosition(Sprite* sprite, Vector2D pos)
{
	Vector2D pivot = sprite->mPivot;

	const float pivotX = MGMath::Clamp(pivot.GetX(), 0.f, 1.f);
	const float pivotY = MGMath::Clamp(pivot.GetY(), 0.f, 1.f);

 	const float startXWorldPosition = pos.GetX() - sprite->mSize.width * pivotX;
	const float startYWorldPosition = pos.GetY() - sprite->mSize.height * pivotY;

	return Vector2D(startXWorldPosition, startYWorldPosition);
}