#ifndef SQLLITEHELPER_H
#define SQLLITEHELPER_H
#include "sqlite3.h"
#include<vector>
#pragma comment(lib, "sqlite3.lib")


class SQLiteHelper
{
public:
	SQLiteHelper() { }
	virtual ~SQLiteHelper() { CloseDB(); }

	// 打开数据库
	static int OpenDB(const char *path);
	// 关闭数据库
	static int CloseDB();
	// 创建一张表
	static int CreateTable(const char *create_table_state);
	// 删除一张表
	static int DropTable(const char *table_name);
	// 查询操作
	static int Select(const char *select_state);
	// 插入操作
	static int Insert(const char *insert_state);
	// 删除操作
	static int Delete(const char *delete_state);
	// 更新操作
	static int Update(const char *update_state);

	//同时创建多个表
	static int CreateTables(std::vector<const char*>  create_tables);
	
	//static sqlite3 * getSqlite3() { return sqlite_db_; }
//private:
	static sqlite3 *sqlite_db_;// 数据库的指针
	static char* err_msg_;		// 错误信息
	static bool is_close_;		// 关闭数据的标识

	// 主要用在selece操作中的显示数据元素
	static int CallBackFunc(void *NotUsed, int argc, char **argv, char **azColName);
	// 执行sql语句
	static int SqlStateExec(const char *sql_state);
};

#endif