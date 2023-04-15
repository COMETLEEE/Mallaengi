#include "LibraryPCH.h"
#include "SoundTable.h"
#include "SoundManager.h"

bool SoundTable::Deserialize(const string& s)
{
	rapidjson::Document doc;

	int i = 0;
	while (s[i] != '[')
	{
		i++;
	}

	string str = s.substr(i);

	if (InitDocument(str, doc))
		return false;

	if (!doc.IsArray())
		return false;

	for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
	{
		SoundTable p;
		p.Deserialize(*itr);
		SoundManager::GetInstance()->GetSoundList().push_back(p);
	}

	return true;
}

bool SoundTable::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartArray();

	//for (std::list<SoundTable>::const_iterator it = mSoundList.begin(); it != mSoundList.end(); it++)
	//{
	//	(*it).doSerialize(writer);
	//}
	writer->EndArray();

	return true;
}

bool SoundTable::Deserialize(const rapidjson::Value& obj)
{
	
	Id(obj["Id"].GetInt());
	SoundName(obj["SoundName"].GetString());
	Loop(obj["Loop"].GetBool());
	IsBgm(obj["IsBgm"].GetBool());
	FileRoot(obj["FileRoot"].GetString());
	return true;
}

bool SoundTable::doSerialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartObject();

	writer->String("Id");
	writer->Int(mId);

	writer->String("Loop");
	writer->Bool(mLoop);

	writer->String("IsBgm");
	writer->Bool(mIsBgm);

	writer->String("SoundName");
	writer->String(mSoundName.c_str());

	writer->String("FileRoot");
	writer->String(mFileRoot.c_str());

	writer->EndObject();

	return true;
}