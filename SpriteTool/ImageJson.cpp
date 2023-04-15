#include "pch.h"
#include "ImageJson.h"

void ImageJson::DataSetup(const rapidjson::Value& obj)
{
	ImageData temp;

	temp.imageID = obj["Id"].GetInt();
	temp.name = obj["Name"].GetString();
	temp.path = obj["Path"].GetString();

	mImageList.push_back(temp);
}

bool ImageJson::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	return true;
}