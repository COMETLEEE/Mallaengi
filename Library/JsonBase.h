#pragma once

//rapidjson
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"		// for stringify JSON
#include "rapidjson/filereadstream.h"	// fopen입출력을 위해..
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/error.h"		// 에러판단을 위해서
#include "rapidjson/error/en.h"
#include "rapidjson/encodedstream.h"

#include <string>

using std::string;

class JsonBase
{
public:
	bool DeserializeFromFile(const string& filePath);
	bool DeserializeFromData(const string& data);
	bool SerializeToFile(const string& filePath);

	virtual string Serialize() const;
	virtual bool Deserialize(const std::string& s);
	virtual bool Deserialize(const rapidjson::Value& obj) = 0;
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer)const = 0;


protected:
	bool InitDocument(const string& s, rapidjson::Document& doc);

};