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

class ImageJson : public Products
{
public:
	vector<ImageData> mImageList;

public:
	void DataSetup(const rapidjson::Value& obj);
	bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};