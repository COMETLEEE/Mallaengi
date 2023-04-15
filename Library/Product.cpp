#include "LibraryPCH.h"
#include "Product.h"

Product::Product():mId(0),mLoop(0),mSoundFileName(0)
{
}

Product::~Product()
{
}

bool Product::Deserialize(const rapidjson::Value& obj)
{
	
	Id(obj["Id"].GetInt());
	SoundFileName(obj["SoundFileName"].GetString());
	Loop(obj["Loop"].GetBool());
	return true;
}

bool Product::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();

	writer->String("Id");
	writer->Int(mId);
		
	writer->String("Loop");
	writer->Bool(mLoop);

	writer->String("SoundFileName");
	writer->String(mSoundFileName.c_str());

	writer->EndObject();

	return true;
}
