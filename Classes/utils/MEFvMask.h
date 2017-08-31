#ifndef __ME_FV_MASK_H__
#define __ME_FV_MASK_H__
#include <string>
#include <vector>
using namespace std;

class MEFvMask
{
public:
	static int Mask(const int flag);
	static bool HasAny(const int flag, const int mask);
	static bool HasAll(const int flag, const int mask);
	static int Add(const int flag, const int mask);
	static int Del(const int flag, const int mask);
	static int Remove(const int flag, const int mask);
	static int IsAdd(const int oldFlag, const int newFlag, const int mask);
	static int IsDel(const int oldFlag, const int newFlag, const int mask);

};

#endif //__ME_FV_MASK_H__