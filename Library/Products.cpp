#include "LibraryPCH.h"
#include "Products.h"

bool Products::Deserialize(const string& s)
{
	rapidjson::Document doc;
	
	int i = 0;
	while (s[i] != '[')
	{
		i++;
	}

	string str = s.substr(i);

	if (InitDocument(str,doc))
	{
		return false;
	}

	if (!doc.IsArray())
	{
		return false;
	}

	for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
	{
		//Product p;
		//p.Deserialize(*itr);
		//mProducts.push_back(p);

		DataSetup(*itr);
	}

	return true;
}

bool Products::DeserializeFile(const string& filePath)
{
	return DeserializeFromFile(filePath);
}

bool Products::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	writer->StartArray();

	for (std::list<Product>::const_iterator it = mProducts.begin(); it != mProducts.end(); it++)
	{
		(*it).Serialize(writer);
	}

	writer->EndArray();

	return true;
}