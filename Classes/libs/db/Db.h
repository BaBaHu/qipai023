#ifndef _Db_H_
#define _Db_H_

#ifdef CO_USE_DB

#include <string>

struct sqlite3;
struct sqlite3_stmt;

typedef int (*DB_EXEC_CALLBACK)(void *userdata, int cols, char **col_values, char **col_names);

class Db
{
public:
	Db();
	~Db();

	bool  open(const char* filepath);
	bool  isOpen() const;
	void  close();
	bool  exec(const char* sql, DB_EXEC_CALLBACK callback=0, void* userdata=0);
	char** query(const char *sql, int *row,int *col);  
	void queryFree(char*** result);
	const char* errMsg() const;

	////////////////////////////////////////////////////////////////////
	// 辅助函数
	bool isTableExist(const char* name);

private:
	sqlite3*	mDb;
	std::string mSql;
	std::string mErrMsg;
};

//int row = 0;
//int col = 0;
//char** result = db.query("select * from account", &row, &col);

//std::string str;
//for (int r = 0; r < row+1; ++r)
//{
//	for (int c = 0; c < col; ++c)
//	{
//		if (r == 0)
//		{// 标题
//			str.append(result[r*col + c]);
//			str.append("\t\t");
//		}
//		else 
//		{
//			str.append(decode(result[r*col + c]));
//			str.append("\t");
//		}

//	}
//	str.append("\n");
//}

//log("%s", str.c_str());
//db.queryFree(&result);

#endif // CO_USE_DB

#endif // _Db_H_