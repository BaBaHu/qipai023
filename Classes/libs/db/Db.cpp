#include "Db.h"

#ifdef CO_USE_DB

#include "sdk/sqlite3/sqlite3.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
Db::Db()
	: mDb(0)
{

}

Db::~Db()
{
	close();
}

bool Db::isOpen() const
{
	return mDb != 0;
}

bool Db::open(const char* filepath)
{
	close();

	mErrMsg.clear();

	int ret = sqlite3_open(filepath, &mDb);

	if (ret != SQLITE_OK)
	{
		mErrMsg.resize(512, '0');
		sprintf(&mErrMsg[0], "open db [%s] failed!!! [code:%d]", filepath, ret);
		printf("%s\n", errMsg());
		return false;
	}

	return true;
}

void Db::close()
{
	if (mDb)
		sqlite3_close(mDb);
		
	mDb	= 0;
	mErrMsg.clear();
}

bool Db::exec(const char* sql, DB_EXEC_CALLBACK callback, void* userdata)
{
	if (mDb == 0)
	{
		mErrMsg = "db is not open";
		printf("%s\n", errMsg());
		return false;
	}

	mErrMsg.clear();
	char* err;
	int ret = sqlite3_exec(mDb, sql, callback, userdata, &err);

	if (ret != SQLITE_OK)
	{
		mErrMsg.resize(512, '\0');
		sprintf(&mErrMsg[0], "exec [%s] failed!!! [code:%d msg:%s]", sql, ret, err);
		printf("%s\n", errMsg());
		sqlite3_free(err);
		return false;
	}

	return true;
}
//
//sqlite3_stmt* Db::queryEx(const char* sql)
//{
//	if (mDb == 0)
//	{
//		mErrMsg = "db is not open";
//		printf("%s\n", errMsg());
//		return 0;
//	}
//
//	mErrMsg.clear();
//	//char* err;
//
//	int starts = 0;
//	sqlite3_stmt* statement = 0;
//	int ret = sqlite3_prepare(mDb, sql, (int)strlen(sql), &statement, 0);
//	
//	if (ret != SQLITE_OK)
//	{
//		mErrMsg.resize(512, '\0');
//		sprintf(&mErrMsg[0], "exec [%s] failed!!! [code:%d]", sql, ret);
//		printf("%s\n", errMsg());
//		sqlite3_free(err);
//		return 0;
//	}
//
//	return statement;
//}

char** Db::query(const char *sql, int *row,int *col)
{
	if (mDb == 0)
	{
		mErrMsg = "db is not open";
		printf("%s\n", errMsg());
		return 0;
	}

	char **result = 0;
	mErrMsg.clear();
	char* err;
	int ret = sqlite3_get_table(mDb, sql, &result, row, col, &err);

	if (ret != SQLITE_OK)
	{
		mErrMsg.resize(1024, '\0');
		sprintf(&mErrMsg[0], "sqlite3_get_table [%s] failed!!! [code:%d msg:%s]", sql, ret, err);
		printf("%s\n", errMsg());
		sqlite3_free(err);
		return 0;
	}

	return result;
}

void Db::queryFree(char*** result)
{
	if (result != 0 && *result != 0)
	{
		sqlite3_free_table(*result);
		*result = 0;
	}
}

const char* Db::errMsg() const
{
	return mErrMsg.c_str();
}

////////////////////////////////////////////////////////////////////
// 辅助函数
bool Db::isTableExist(const char* name)
{
	std::string sql = "";
	sql.append("select count(*) from sqlite_master where type='table' and name='");
	sql.append(name);
	sql.append("'");
	return exec(sql.c_str());
}

#endif // CO_USE_DB