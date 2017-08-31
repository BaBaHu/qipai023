#ifndef _JsonMake_H_
#define _JsonMake_H_

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;
using namespace rapidjson;

class JsonMake : public Ref
{
public:
	CREATE_FUNC(JsonMake);
public:
	JsonMake();
	~JsonMake();
	virtual bool init();
	std::string getJsonMyBaodanMain();

};

#endif // _JsonMake_H_