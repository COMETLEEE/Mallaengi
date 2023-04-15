#pragma once
#include <vector>
#include <d2d1.h>
using std::vector;

// Json
#include "..\\Library\\Products.h"
#pragma comment(lib, "..\\..\\Output\\Library.lib")
#pragma comment(lib, "d2d1.lib")

/// <summary>
/// 선택한 Item의 데이터를 저장하여
/// 출력 및 타일 입력시에 전달하기 위한 구조체
/// 
/// 2022. 02. 07 JK
/// </summary>
struct ItemData
{
	UINT ID;		// Item ID
	string name;
	vector<INT> group;
	UINT imageID;	// Image ID
	CD2DRectF imageRect;
	UINT layer;		// 레이어 - Sort Order
};

/// <summary>
/// Tile 데이터 읽어오는 클래스
/// 
/// 2022. 02. 09 JK
/// </summary>
class ItemJson : public Products
{
public:
	vector<ItemData> mItemList;

public:
	void DataSetup(const rapidjson::Value& obj);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};

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
/// 이미지 데이터 읽어오는 클래스
/// 
/// 2022. 02. 18 JK
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
/// 맵 데이터 구조체
/// 
/// 2022. 02. 07 JK
/// </summary>
struct TileData
{
	UINT ID;				// Item ID
	string type;			// 타일 타입
	UINT index;				// 타일 주소
	vector<INT> group;		// 연결된 객체
	UINT imageID;			// Image ID
	CD2DRectF imageRect;	// 이미지 내에서의 영역
	UINT layer;				// 레이어 - Sort Order
};

/// <summary>
/// 맵 데이터 읽고 쓰기위한 클래스
/// 
/// 2022. 02. 18 JK
/// </summary>
class MapJson : public Products
{
public:
	vector<TileData> mTileList;

public:
	void DataSetup(const rapidjson::Value& obj);
	void SaveData(const string& filePath, vector<vector<TileData>> tiles, vector<vector<vector<TileData>>> objects);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	string MapJson::SerializeToMFC();
};