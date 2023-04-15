#include "PreCompiledHeader.h"
#include "JsonManager.h"

void ItemJson::DataSetup(const rapidjson::Value& obj)
{
	ItemData temp;

	temp.ID = obj["Id"].GetInt();
	temp.name = obj["Name"].GetString();

	for (int i = 0; i < obj["Group"].GetArray().Size(); i++)
	{
		int num = obj["Group"].GetArray()[i].GetInt();

		if (num != 0)
			temp.group.push_back(num);
	}

	temp.imageID = obj["ImageID"].GetInt();

	FLOAT temp2[4] = {};

	for (int i = 0; i < 4; i++)
		temp2[i] = obj["RECT"].GetArray()[i].GetInt();

	temp.imageRect = { temp2[0], temp2[1], temp2[2], temp2[3] };

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
	temp.imageID = obj["ImageID"].GetInt();
	temp.layer = obj["Layer"].GetInt();

	FLOAT temp2[4] = {};

	for (int i = 0; i < 4; i++)
		temp2[i] = obj["RECT"].GetArray()[i].GetInt();

	for (int i = 0; i < obj["Group"].GetArray().Size(); i++)
	{
		int num = obj["Group"].GetArray()[i].GetInt();

		temp.group.push_back(num);
	}

	temp.imageRect = { temp2[0], temp2[1], temp2[2], temp2[3] };

	mTileList.push_back(temp);
}

//void MapJson::SaveData(const string& filePath, const std::vector<std::vector<TileData>>& tiles)
//{
//	for (int i = 0; i < tiles.size(); i++)
//	{
//		for (int j = 0; j < tiles[i].size(); j++)
//		{
//			if (tiles[i][j].ID != 0)
//			{
//				mTileList.push_back(tiles[i][j]);
//				mTileList.back().index = (i << 16) + (j & 0xffff);
//
//				if (tiles[i][j].group.front() != 0)
//				{
//					for (int k = 0; k < tiles[i][j].group.size(); k++)
//					{
//						INT index = tiles[i][j].group[k];
//
//						tiles[i + index >> 16][j + (index & 0xffff)] = {};
//					}
//				}
//			}
//		}
//	}
//
//	SerializeToFile(filePath);
//}

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

void MapJson::DeserializeFromCArchive(const string& path)
{
	CFile file;
	CFileException e;

	if (file.Open(path.c_str(), CFile::modeRead, &e) == true)
	{
		CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);

		CString str;
		string data = "";
		ar >> str;
		data = CT2CA(str);

		DeserializeFromData(data);
	}
}

void NarrativeJson::DataSetup(const rapidjson::Value& obj)
{
	NarrativeData temp;

	temp.imageID = obj["ImageID"].GetInt();
	temp.delay = obj["Delay"].GetDouble();
	temp.duration = obj["Duration"].GetDouble();
	temp.alphaSpeed = obj["AlphaSpeed"].GetInt();

	if (temp.delay < 0.0f)
		temp.delay = 0.10f;

	if (temp.duration < 0.0f)
		temp.duration = 0.0f;

	if (temp.alphaSpeed < 0.1f)
		temp.alphaSpeed = 0.1f;
	else if (temp.alphaSpeed > 1.0f)
		temp.alphaSpeed = 1.0f;

	FLOAT temp2[2] = {};

	for (int i = 0; i < 2; i++)
		temp2[i] = obj["ImagePos"].GetArray()[i].GetInt();

	temp.imagePos = { temp2[0], temp2[1] };

	for (int i = 0; i < 2; i++)
		temp2[i] = obj["ImageSize"].GetArray()[i].GetInt();

	temp.imageSize = { temp2[0], temp2[1] };

	mNarrativeList.push_back(temp);
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

	temp.pivot = { static_cast<float>(temp2[0]), static_cast<float>(temp2[1]) };

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
		writer->Int(mSpriteList[i].pivot.mX);
		writer->Int(mSpriteList[i].pivot.mY);
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

void SpriteJson::DeserializeFromCArchive(const string& path)
{
	CFile file;
	CFileException e;

	if (file.Open(path.c_str(), CFile::modeRead, &e) == true)
	{
		CArchive ar(&file, CArchive::load | CArchive::bNoFlushOnDelete);

		CString str;
		string data = "";
		ar >> str;
		data = CT2CA(str);

		DeserializeFromData(data);
	}
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
		writer->Int(mSpriteList[i].pivot.mX);
		writer->Int(mSpriteList[i].pivot.mY);
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