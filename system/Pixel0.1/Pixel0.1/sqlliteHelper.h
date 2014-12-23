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

	// �����ݿ�
	static int OpenDB(const char *path);
	// �ر����ݿ�
	static int CloseDB();
	// ����һ�ű�
	static int CreateTable(const char *create_table_state);
	// ɾ��һ�ű�
	static int DropTable(const char *table_name);
	// ��ѯ����
	static int Select(const char *select_state);
	// �������
	static int Insert(const char *insert_state);
	// ɾ������
	static int Delete(const char *delete_state);
	// ���²���
	static int Update(const char *update_state);

	//ͬʱ���������
	static int CreateTables(std::vector<const char*>  create_tables);
	
	//static sqlite3 * getSqlite3() { return sqlite_db_; }
//private:
	static sqlite3 *sqlite_db_;// ���ݿ��ָ��
	static char* err_msg_;		// ������Ϣ
	static bool is_close_;		// �ر����ݵı�ʶ

	// ��Ҫ����selece�����е���ʾ����Ԫ��
	static int CallBackFunc(void *NotUsed, int argc, char **argv, char **azColName);
	// ִ��sql���
	static int SqlStateExec(const char *sql_state);
};

#endif