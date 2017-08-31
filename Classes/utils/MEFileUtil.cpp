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

//�ݹ鴴��Ŀ¼(�����༶,absolutePath�����·����), �Զ����Ŀ¼�Ƿ����
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

/*  ���ʵ��ֻ��һ��˼·������Ҫ�õ�ʱ���ǻὫ��ʵ���ڴ�������node�У��ټ��ϸ�����Ҫ������  */
bool  MEFileUtil::checkSpritePixel(int locationXInNode, int locationYInNode, std::string fileName)
{
	auto locationInNode = ccp(locationXInNode, locationYInNode);
	//���غ�mysprite��ͬ��ͼƬ������ʵ�ֵ�png�ģ�alphaͨ���ܺ���
	Image *myImage = new Image();
	myImage->initWithImageFile(fileName);
	unsigned char *data = myImage->getData();  //�������ͼƬ������
	//���ݸոռ�����������ֵ��������������������һ�����ص�      Ȼ������ȡ�������ص��alphaֵ
	//ע�⣺��ΪͼƬ���꣨0��0���������Ͻǣ�����Ҫ�ʹ������Yת��һ�£�Ҳ���ǡ�(myImage->getHeight() - (int)(ps.y) - 1)��
	int pa = 4 * ((myImage->getHeight() - (int)(locationInNode.y) - 1) * myImage->getWidth() + (int)(locationInNode.x)) + 3;
	unsigned int ap = data[pa];
	//�ж�alphaֵ��Ϊ��ʱ��Ҳ���Ǵ������˲�����sprite����ͼ��ĵط�����ʱ�ٴ�����Ҫ���߼����ݾͺ���
	if (ap != 0)
	{
		CCLOG("check");
		return true;
	}
	return false;
}