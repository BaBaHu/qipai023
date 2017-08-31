#ifndef _CSocketMission_H_
#define _CSocketMission_H_
#include "ISocketEngine.h"

class CSocketMission
	: public ISocketEngineSink
{
public:
	CSocketMission(const std::string& url, int port=0);
	virtual ~CSocketMission();

	void setUrl(const std::string& url, int port);
	void start();
	void stop();
	bool isAlive() const;
	bool send(int main, int sub);
	bool send(int main, int sub, void* data, int size);
private:
	ISocketEngine* mSocketEngine;
	std::string mUrl;
	int  mPort;
}; // CSocketMission

#endif // _CSocketMission_H_