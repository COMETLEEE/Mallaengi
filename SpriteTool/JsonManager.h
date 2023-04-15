#pragma once
#include <vector>

using std::vector;

// Json
#include "..\\Library\\Products.h"
#pragma comment(lib, "..\\..\\Output\\Library.lib")

/// <summary>
/// 이미지 데이터를 다루기 위한 구조체
/// 
/// 2022. 02. 09 JK
/// </summary>
struct ImageData
{
	UINT imageID;
	CString name;
	CString path;
};

/// <summary>
/// 원본 이미지용 제이슨 클래스
/// 
/// 2022. 02. 16 JK 
/// </summary>
class ImageJson : public Products
{
public:
	vector<ImageData> mImageList;

public:
	void DataSetup(const rapidjson::Value& obj);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};

/// <summary>
/// 콜라이더 정보를 위한 구조체
/// 
/// 2022. 02. 17 JK
/// </summary>
struct ColliderInfo
{
	D2D1_RECT_F rect;
	INT type;
};

/// <summary>
/// 스프라이트 정보를 저장하는 구조체
/// 
/// 2022. 02. 15 JK
/// </summary>
struct SpriteInfo
{
	UINT imageID;
	D2D1_RECT_F imageRect;
	double duration;
	CPoint pivot;
	ColliderInfo collider;
};

/// <summary>
/// 스프라이트 데이터 제이슨
/// 
/// 2022. 02. 16 JK
/// </summary>
class SpriteJson : public Products
{
public:
	vector<SpriteInfo> mSpriteList;

public:
	void DataSetup(const rapidjson::Value& obj);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	string SerializeToMFC();
};