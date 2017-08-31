#include "MEFileUtil.h"
#include "CCLuaEngine.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	#include <unistd.h>
    #include <sys/stat.h>
#else
    #include <commdlg.h>
    #include "windows.h"
	#include <io.h>
	#include <direct.h>
#endif

#include <stdio.h>
#include <math.h>
#include <thread>
USING_NS_CC;

bool MEFileUtil::existFile(std::string fileName)
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	return (access(fullPath.c_str(),0)==0);
#else
	return (_access(fullPath.c_str(),0)==0);
#endif
}

int  MEFileUtil::createDir(std::string fileName)
{
	char   DirName[256];  
	strcpy(DirName, fileName.c_str());
	int   i,len   =   strlen(DirName);  
	if(DirName[len-1]!='/')
		strcat(DirName,   "/");
	len   =   strlen(DirName);
	for(i=1;   i<len;   i++)  
	{
		if(DirName[i]=='/')
		{
			DirName[i]   =   0;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
			if(access(DirName,0)!=0 && mkdir(DirName, 0777) == -1)
#else
			if(_access(DirName,0)!=0 && _mkdir(DirName)==-1)
#endif
			{
				perror("mkdir   error");
				return   -1;
			}		

			DirName[i]   =   '/';
		}
	}
	return   0;  
}

int	MEFileUtil::getFileLength(std::string fileName)
{
	int iSize = 0;
	do
	{
		// read the file from hardware
		std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
		FILE *fp = fopen(fullPath.c_str(), "rb");
		CC_BREAK_IF(!fp);

		fseek(fp,0,SEEK_END);
		iSize = ftell(fp);
		fclose(fp);
	} while (0);

	return iSize;
}

void MEFileUtil::destroyDirectory(std::string absolutePath)
{
	// Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	std::string command = "rm -r ";
	// Path may include space.
	command += "\"" + absolutePath + "\"";
	system(command.c_str());    
#else
	std::string command = "rd /s /q ";
	// Path may include space.
	command += "\"" + absolutePath + "\"";
	system(command.c_str());
#endif
}

//递归创建目录(包括多级,absolutePath需绝对路径名), 自动检测目录是否存在
bool MEFileUtil::createDirectory(std::string absolutePath)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	return FileUtils::getInstance()->createDirectory(absolutePath);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	bool ret = CreateDirectoryA(absolutePath.c_str(), nullptr);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
	return true;
#else
	mode_t processMask = umask(0);
	int ret = mkdir(absolutePath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		return false;
	}
	return true;
#endif
}

bool  MEFileUtil::IsValidRight(int Num1, int Num2)
{
	if (Num1 & Num2)
	{
		return true;
	}
	return false;
}

int  MEFileUtil::getLogValue(int Num)
{
	//log2(x)=log(x)/log(2);
	return (int)(log(Num) / log(2));
}

/*  这个实现只是一个思路，真正要用的时候还是会将它实现在触摸对象node中，再加上各种需要的属性  */
bool  MEFileUtil::checkSpritePixel(int locationXInNode, int locationYInNode, std::string fileName)
{
	auto locationInNode = ccp(locationXInNode, locationYInNode);
	//加载和mysprite相同的图片，我是实现的png的，alpha通道很好用
	Image *myImage = new Image();
	myImage->initWithImageFile(fileName);
	unsigned char *data = myImage->getData();  //这里就是图片数据了
	//根据刚刚计算的相对坐标值，计算出触摸点代表了哪一个像素点      然后再提取出该像素点的alpha值
	//注意：因为图片坐标（0，0）是在左上角，所以要和触摸点的Y转换一下，也就是“(myImage->getHeight() - (int)(ps.y) - 1)”
	int pa = 4 * ((myImage->getHeight() - (int)(locationInNode.y) - 1) * myImage->getWidth() + (int)(locationInNode.x)) + 3;
	unsigned int ap = data[pa];
	//判断alpha值不为零时，也就是触摸在了不规则sprite的有图像的地方，这时再处理需要的逻辑内容就好了
	if (ap != 0)
	{
		CCLOG("check");
		return true;
	}
	return false;
}