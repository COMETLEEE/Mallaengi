#include "pch.h"
#include "JsonManager.h"

void ItemJson::DataSetup(const rapidjson::Value& obj)
{
	ItemData temp;

	temp.ID = obj["Id"].GetInt();
	temp.name = obj["Name"].GetString();

	for (int i = 0; i < obj["Group"].GetArray().Size(); i++)
	{
		int num = obj["Group"].GetArray()[i].GetInt();

		temp.group.push_back(num);
	}

	temp.imageID = obj["ImageID"].GetInt();

	FLOAT temp2[4] = {};

	for (int i = 0; i < 4; i++)
		temp2[i] = obj["RECT"].GetArray()[i].GetInt();

	temp.imageRect = { temp2[0], temp2[1], temp2[2], temp2[3] };

	if (obj.HasMember("Layer"))
		temp.layer = obj["Layer"].GetInt();
	else
		temp.layer = 0;

	mItemList.push_back(temp);
}

bool ItemJson::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	return true;
}

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

void MapJson::DataSetup(const rapidjson::Value& obj)
{
	TileData temp;

	temp.ID = obj["Id"].GetInt();
	temp.type = obj["Type"].GetString();
	temp.index = obj["Index"].GetInt();

	ItemJson tileJson;
	tileJson.DeserializeFromFile("Json\\TileResourceTable.json");

	bool find = false;

	for (int i = 0; i < tileJson.mItemList.size(); i++)
	{
		if (tileJson.mItemList[i].ID == temp.ID)
		{
			temp.imageID = tileJson.mItemList[i].imageID;
			temp.imageRect = tileJson.mItemList[i].imageRect;
			temp.group = tileJson.mItemList[i].group;
			temp.layer = tileJson.mItemList[i].layer;

			find = true;

			break;
		}
	}

	if (find == false)
	{
		ItemJson objectJson;
		objectJson.DeserializeFromFile("Json\\ObjectResourceTable.json");

		for (int i = 0; i < objectJson.mItemList.size(); i++)
		{
			if (objectJson.mItemList[i].ID == temp.ID)
			{
				temp.imageID = objectJson.mItemList[i].imageID;
				temp.imageRect = objectJson.mItemList[i].imageRect;
				temp.group = objectJson.mItemList[i].group;
				temp.layer = objectJson.mItemList[i].layer;

				find = true;

				break;
			}
		}

		if (find == false)
			assert(!_T("Map Json중 ID가 잘못된 데이터가 존재합니다."));
	}

	mTileList.push_back(temp);
}

void MapJson::SaveData(const string& filePath, vector<vector<TileData>> tiles, vector<vector<vector<TileData>>> objects)
{
}

bool MapJson::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartArray();

	for (int i = 0; i < mTileList.size(); i++)
	{
		writer->StartObject();

		writer->String("Id");
		writer->Int(mTileList[i].ID);

		writer->String("Type");
		writer->String(mTileList[i].type.c_str());

		writer->String("Index");
		writer->Int(mTileList[i].index);

		writer->String("ImageID");
		writer->Int(mTileList[i].imageID);

		writer->String("RECT");
		writer->StartArray();
		writer->Int(mTileList[i].imageRect.left);
		writer->Int(mTileList[i].imageRect.top);
		writer->Int(mTileList[i].imageRect.right);
		writer->Int(mTileList[i].imageRect.bottom);
		writer->EndArray();

		writer->String("Group");
		writer->StartArray();
		if (mTileList[i].group.empty())
		{
			writer->Int(0);
		}
		else
		{
			for (int j = 0; j < mTileList[i].group.size(); j++)
				writer->Int(mTileList[i].group[j]);
		}
		writer->EndArray();

		writer->String("Layer");
		writer->Int(mTileList[i].layer);

		writer->EndObject();
	}

	writer->EndArray();

	return true;
}

string MapJson::SerializeToMFC()
{
	rapidjson::StringBuffer ss;
	rapidjson::Writer<rapidjson::StringBuffer> why(ss);
	rapidjson::Writer<rapidjson::StringBuffer>* writer = &why;

	writer->StartArray();

	for (int i = 0; i < mTileList.size(); i++)
	{
		writer->StartObject();

		writer->String("Id");
		writer->Int(mTileList[i].ID);

		writer->String("Type");
		writer->String(mTileList[i].type.c_str());

		writer->String("Index");
		writer->Int(mTileList[i].index);

		writer->String("ImageID");
		writer->Int(mTileList[i].imageID);

		writer->String("RECT");
		writer->StartArray();
		writer->Int(mTileList[i].imageRect.left);
		writer->Int(mTileList[i].imageRect.top);
		writer->Int(mTileList[i].imageRect.right);
		writer->Int(mTileList[i].imageRect.bottom);
		writer->EndArray();

		writer->String("Group");
		writer->StartArray();
		if (mTileList[i].group.empty())
		{
			writer->Int(0);
		}
		else
		{
			for (int j = 0; j < mTileList[i].group.size(); j++)
				writer->Int(mTileList[i].group[j]);
		}
		writer->EndArray();

		writer->String("Layer");
		writer->Int(mTileList[i].layer);

		writer->EndObject();
	}

	writer->EndArray();

	return ss.GetString();
}