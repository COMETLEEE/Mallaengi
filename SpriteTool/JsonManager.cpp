#include "pch.h"
#include "JsonManager.h"

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

void SpriteJson::DataSetup(const rapidjson::Value& obj)
{
	SpriteInfo temp;

	// Image ID
	temp.imageID = obj["ImageID"].GetInt();

	// Image Rect
	FLOAT temp2[4] = {};

	for (int i = 0; i < 4; i++)
		temp2[i] = obj["ImageRect"].GetArray()[i].GetInt();

	temp.imageRect = { temp2[0], temp2[1], temp2[2], temp2[3] };

	// Pivot
	for (int i = 0; i < 2; i++)
		temp2[i] = obj["Pivot"].GetArray()[i].GetInt();

	temp.pivot = { static_cast<INT>(temp2[0]), static_cast<INT>(temp2[1]) };

	// Duration
	temp.duration = obj["Duration"].GetDouble();

	// Collider Type
	temp.collider.type = obj["ColliderType"].GetInt();

	// Collider Rect
	for (int i = 0; i < 4; i++)
		temp2[i] = obj["ColliderRect"].GetArray()[i].GetInt();

	temp.collider.rect = { temp2[0], temp2[1], temp2[2], temp2[3] };

	mSpriteList.push_back(temp);
}

bool SpriteJson::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartArray();

	for (int i = 0; i < mSpriteList.size(); i++)
	{
		writer->StartObject();

		writer->String("ImageID");
		writer->Int(mSpriteList[i].imageID);

		writer->String("ImageRect");
		writer->StartArray();
		writer->Int(mSpriteList[i].imageRect.left);
		writer->Int(mSpriteList[i].imageRect.top);
		writer->Int(mSpriteList[i].imageRect.right);
		writer->Int(mSpriteList[i].imageRect.bottom);
		writer->EndArray();

		writer->String("Duration");
		writer->Double(mSpriteList[i].duration);
		writer->EndArray();

		writer->String("Pivot");
		writer->StartArray();
		writer->Int(mSpriteList[i].pivot.x);
		writer->Int(mSpriteList[i].pivot.y);
		writer->EndArray();

		writer->String("ColliderType");
		writer->Int(mSpriteList[i].collider.type);

		writer->String("ColliderRect");
		writer->StartArray();
		writer->Int(mSpriteList[i].collider.rect.left);
		writer->Int(mSpriteList[i].collider.rect.top);
		writer->Int(mSpriteList[i].collider.rect.right);
		writer->Int(mSpriteList[i].collider.rect.bottom);

		writer->EndObject();
	}

	writer->EndArray();

	return true;
}

string SpriteJson::SerializeToMFC()
{
	rapidjson::StringBuffer ss;
	rapidjson::Writer<rapidjson::StringBuffer> why(ss);
	rapidjson::Writer<rapidjson::StringBuffer>* writer = &why;

	writer->StartArray();

	for (int i = 0; i < mSpriteList.size(); i++)
	{
		writer->StartObject();

		writer->String("ImageID");
		writer->Int(mSpriteList[i].imageID);

		writer->String("ImageRect");
		writer->StartArray();
		writer->Int(mSpriteList[i].imageRect.left);
		writer->Int(mSpriteList[i].imageRect.top);
		writer->Int(mSpriteList[i].imageRect.right);
		writer->Int(mSpriteList[i].imageRect.bottom);
		writer->EndArray();

		writer->String("Duration");
		writer->Double(mSpriteList[i].duration);

		writer->String("Pivot");
		writer->StartArray();
		writer->Int(mSpriteList[i].pivot.x);
		writer->Int(mSpriteList[i].pivot.y);
		writer->EndArray();

		writer->String("ColliderType");
		writer->Int(mSpriteList[i].collider.type);

		writer->String("ColliderRect");
		writer->StartArray();
		writer->Int(mSpriteList[i].collider.rect.left);
		writer->Int(mSpriteList[i].collider.rect.top);
		writer->Int(mSpriteList[i].collider.rect.right);
		writer->Int(mSpriteList[i].collider.rect.bottom);
		writer->EndArray();

		writer->EndObject();
	}

	writer->EndArray();

	return ss.GetString();
}