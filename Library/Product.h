#pragma once
#include "JsonBase.h"
#include <Windows.h>

class Product : public JsonBase
{
public:
	Product();
	virtual ~Product();

	virtual bool Deserialize(const rapidjson::Value& obj);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

	//// Getters/Setters.
	int Id() const { return mId; }
	void Id(int id) { mId = id; }

	const string& SoundFileName() const { return mSoundFileName; }
	void SoundFileName(const string& SoundFileName) { mSoundFileName = SoundFileName; }

	bool Loop() const { return mLoop; }
	void Loop(int Loop) { mLoop = Loop; }


private:
	int mId;
	bool mLoop;
	string mSoundFileName;

};

