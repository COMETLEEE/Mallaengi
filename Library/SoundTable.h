#pragma once
#include "JsonBase.h"

class SoundTable : public JsonBase
{
public:
	virtual ~SoundTable() {};

	// Getters/Setters.
	//list<SoundTable>& SoundList() { return mSoundList; }
public:
	virtual bool Deserialize(const std::string& s);
	virtual bool Deserialize(const rapidjson::Value& obj);
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	virtual bool doSerialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;

public:
	const std::string& SoundName() const { return mSoundName; }
	void SoundName(const std::string& soundname) { mSoundName = soundname; }

	const std::string& FileRoot() const { return mFileRoot; }
	void FileRoot(const std::string& fileRoot) { mFileRoot = fileRoot; }

	bool Loop() const { return mLoop; }
	void Loop(bool loop) { mLoop = loop; }

	bool IsBgm() const { return mIsBgm; }
	void IsBgm(bool isBgm) { mIsBgm = isBgm; }

	int Id() const { return mId; }
	void Id(int id) { mId = id; }

private:
	std::string mSoundName;
	std::string mFileRoot;
	bool mLoop;
	bool mIsBgm;
	int mId;
};

