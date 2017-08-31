#include "MEFvMask.h"

int MEFvMask::Mask(const int flag)
{
	return (0X01 << (flag));
}

bool MEFvMask::HasAny(const int flag, const int mask)
{
	return ((flag&mask) != 0);
}

bool MEFvMask::HasAll(const int flag, const int mask)
{
	return ((flag&mask) == mask);
}

int  MEFvMask::Add(const int flag, const int mask)
{
	return flag | mask;
}

int MEFvMask::Del(const int flag, const int mask)
{
	return flag & ~mask;
}

int MEFvMask::Remove(const int flag, const int mask)
{
	return (flag & (~mask));
}

int MEFvMask::IsAdd(const int oldFlag, const int newFlag, const int mask)
{
	return (((oldFlag&mask) == 0) && ((newFlag&mask) != 0));
}

int MEFvMask::IsDel(const int oldFlag, const int newFlag, const int mask)
{
	return (((oldFlag&mask) != 0) && ((newFlag&mask) == 0));
}