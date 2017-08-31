#ifndef __ME_FILE_UTIL_H__
#define __ME_FILE_UTIL_H__
#include <string>
#include <vector>
using namespace std;

class MEFileUtil
{
public:
	static bool existFile(std::string fileName);
	static int	createDir(std::string fileName);
	static int	getFileLength(std::string fileName);

	static void destroyDirectory(std::string absolutePath);
	static bool createDirectory(std::string absolutePath);

	static bool  IsValidRight(int Num1, int Num2);
	static int   getLogValue(int Num);
	static bool  checkSpritePixel(int locationXInNode, int locationYInNode, std::string fileName);
};

#endif // !__ME_FILE_UTIL_H__