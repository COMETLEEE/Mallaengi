#pragma once

// 라이브러리를 사용해서 
#include "..\\Library\\Products.h"
#pragma comment(lib, "..\\..\\Output\\Library.lib")

struct NarrativeData
{
	UINT imageID;
	Vector2D imagePos;
	D2D1_SIZE_F imageSize;
	double delay;
	double duration;
	int alphaSpeed;
};

class NarrativeJson : public Products
{
public:
	std::vector<NarrativeData> mNarrativeList;

public:
	void DataSetup(const rapidjson::Value& obj);
};

/**
 * 선택한 Item의 데이터를 저장하여 출력 및 타일 입력 시에 전달.
 */
struct ItemData
{
	UINT ID;
	std::string name;
	std::vector<INT> group;
	UINT imageID;
	D2D1_RECT_F imageRect;
	UINT layer;
};

class ItemJson : public Products
{
public:
	std::vector<ItemData> mItemList;

public:
	void DataSetup(const rapidjson::Value& obj);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};

/**
 * 이미지 데이터를 다루기 위한 구조체
 */
struct ImageData
{
	UINT imageID;
	std::string name;
	std::string path;
};

class ImageJson : public Products
{
public:
	std::vector<ImageData> mImageList;

public:
	void DataSetup(const rapidjson::Value& obj);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};

// 맵 데이터 구조체
struct TileData
{
	UINT ID;
	std::string type;
	UINT index;
	std::vector<INT> group;
	UINT imageID;
	D2D1_RECT_F imageRect;
	UINT layer;
};

class MapJson : public Products
{
public:
	std::vector<TileData> mTileList;

public:
	void DataSetup(const rapidjson::Value& obj);
	// void SaveData(const string& filePath, const std::vector<std::vector<TileData>>& tiles);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	void DeserializeFromCArchive(const string& path);
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
	Vector2D pivot;
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
	std::vector<SpriteInfo> mSpriteList;

public:
	void DataSetup(const rapidjson::Value& obj);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	void DeserializeFromCArchive(const string& path);
	string SerializeToMFC();
};