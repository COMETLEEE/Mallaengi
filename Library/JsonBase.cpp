#include "LibraryPCH.h"
#include "JsonBase.h"

string JsonBase::Serialize() const
{
	rapidjson::StringBuffer ss;
	rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
	if (Serialize(&writer))
	{
		return ss.GetString();
	}
	return "";
}

bool JsonBase::Deserialize(const string& s)
{
	
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
	{
		return false;
	}
	Deserialize(doc);
	return true;
}

bool JsonBase::DeserializeFromFile(const string& filePath)
{
	
	ifstream f(filePath);
	stringstream buffer;
	buffer << f.rdbuf();
	f.close();

	return Deserialize(buffer.str());
}

bool JsonBase::DeserializeFromData(const string& data)
{
	stringstream buffer;
	buffer << data.c_str();

	return Deserialize(buffer.str());
}

bool JsonBase::SerializeToFile(const string& filePath)
{
	ofstream f(filePath);
	string s = Serialize();
	f << s;
	f.flush();
	f.close();
	return true;
}

bool JsonBase::InitDocument(const string& s, rapidjson::Document& doc)
{
	if (s.empty())
	{
		return false;
	}

	string validJson(s);
	return doc.Parse(validJson.c_str()).HasParseError() ? true : false;
}