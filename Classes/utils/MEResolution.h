#ifndef __MERESOLUTION_H__
#define __MERESOLUTION_H__

class MEResolution
{
public:
	static void setResolutionRect(int designWidth, int designHeight, int screenWidth, int screenHeight);
	static void setDefaultRect();
protected:
	static void adjustResolution();
private:
	static int s_screenWidth;
	static int s_screenHeight;
	static int s_designWidth;
	static int s_designHeight;
};

#endif