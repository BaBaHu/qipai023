#include "JsonMake.h"

JsonMake::JsonMake()
{

}

JsonMake::~JsonMake()
{

}

bool JsonMake::init()
{
	bool bRet = false;
	do{
		bRet = true;
	} while (0);
	return bRet;
}

std::string JsonMake::getJsonMyBaodanMain()
{
	rapidjson::Document document;
	document.SetObject();

	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value object1(rapidjson::kObjectType);
	rapidjson::Value object2(rapidjson::kObjectType);
	rapidjson::Value object3(rapidjson::kObjectType);
	rapidjson::Value object4(rapidjson::kArrayType);

	object1.AddMember("Name", "Yuxikuo", allocator);
	object1.AddMember("Age", "18", allocator);
	object1.AddMember("Sex", "man", allocator);

	object2.AddMember("Name", "WangDongGe", allocator);
	object2.AddMember("Age", "32", allocator);
	object2.AddMember("Sex", "woman", allocator);

	object3.AddMember("Name", "zhanhong", allocator);
	object3.AddMember("Age", "20", allocator);
	object3.AddMember("Sex", "man", allocator);

	object4.PushBack(object1, allocator);
	object4.PushBack(object2, allocator);
	object4.PushBack(object3, allocator);

	document.AddMember("info", object4, allocator);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s", buffer.GetString());

	return StringUtils::format("%s", buffer.GetString());
}