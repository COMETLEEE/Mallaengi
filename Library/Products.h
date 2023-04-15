#pragma once
#include "JsonBase.h"
#include "Product.h"
#include <list>

using std::list;

class Products : public JsonBase
{
public:
	virtual ~Products() {};
	virtual bool Deserialize(const string& s);
	bool DeserializeFile(const string& filePath);

	// Getters/Setters.
	list<Product>& ProductsList() { return mProducts; }
public:
	virtual void DataSetup(const rapidjson::Value& obj) abstract;
	virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
	virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
private:
	list<Product> mProducts;
};

