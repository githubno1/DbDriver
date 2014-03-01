#pragma once

#include <vector>
#include "SqlDef.h"
using namespace std;

#ifdef _AFX_COMMON_DBLIB_
	#define COMMON_DBLIB __declspec(dllexport)
#else
	#define COMMON_DBLIB __declspec(dllimport)
	#ifdef _DEBUG
		#pragma comment(lib, "DbDriverD.lib")
	#else
		#pragma comment(lib, "DbDriver.lib")
	#endif
#endif


class CSqlDriver;
class CSqlDatabasePrivate;
class CSqlQueryPrivate;
class CSqlRecordset;

class COMMON_DBLIB CSqlDataBase
{
public:
	CSqlDataBase();
	CSqlDataBase(const CSqlDataBase &other);
	~CSqlDataBase();

	CSqlDataBase &operator=(const CSqlDataBase &other);

	// �������ݿ�
	bool open();
	bool open(const char* user, const char* password);
	
	void close();
	bool IsOpen() const;
	bool IsOpenError() const;
	
	// �ж�driver�Ƿ�Ϊ��
	bool isValid() const;

	// ����������Ϣ(һ���������е���Ϣ)
	void setConnctInfo(const char*  dbname, const char* host = NULL, const char* user_name = NULL, 
		const char*  password = NULL, int p = -1);

	// ������������������Ϣ
	void setDatabaseName(const char* name);
	void setUserName(const char* name);
	void setPassword(const char*  password);
	void setHostName(const char*  host);
	void setPort(int p);

	// ��ȡ������Ϣ
	void databaseName(char *szDb) const;
	void userName(char *user) const;
	void password(char *psw) const;
	void hostName(char *host) const;
	int  port() const;

	// ����
	bool BeginTransaction();
	bool CommitTransaction();
	bool RollbackTransaction();

	// ��ȡdriverָ��(�ڲ�ʹ�ã�һ�㲻��ʹ��)
	void* driver() const;

	// ִ�зǲ�ѯ��SQL���
	// ����ֵ: -1-����������,0-ִ��ʧ��,1-ִ�гɹ�
	int ExecuteSql(const char *szSql);

	// ����ִ��sql���(ʹ������)
	int ExecuteSql(char**& strSql,long len);

	// �����Ʋ����󶨵ķ�ʽִ��Sql���ִ�к���
	// nParamsNum:��������; pParas����ֵ
	// 
	int ExecBinary(const char* strSql, byte** pParas,int *len, int nParamsNum);

	// ��Ҫ��Ϊ�˲������������(��ʱû��ʵ�֣�����ʵ��)
	bool PutBlob(const char *strWhereSql, const char *szTableName, const char* szFldName, byte*szVal, long len);

	// �½�һ������,����Ϊ���ݿ�����
	static CSqlDataBase* addDatabase(short type);
	static CSqlDataBase addDatabase(void* driver, const char* connectionName);
	
	// �ͷ�����
	static void freeDatabase(CSqlDataBase *&pDb);

	// ȡ������Ϣ
	void GetLastError(char *szError);
public:
	void GetDbName(char *szDbName, short len);
	short GetDbType();

	// ���ӳ�ʹ��
	virtual short GetPoolFlag();
	virtual short SetPoolFlag(short poolflag);

protected:
	explicit CSqlDataBase(short type);
	explicit CSqlDataBase(void* driver);
	inline void qAtomicAssign(CSqlDatabasePrivate *&d, CSqlDatabasePrivate *x);

private:
	friend class CSqlDatabasePrivate;
	CSqlDatabasePrivate *d;

	short m_poolflag;	//���ӳ�ʹ�ã� 0-δ 1-����Pool
	short m_dbType;
};


class COMMON_DBLIB CSqlQuery
{
public:
	CSqlQuery(){d = NULL;}
	explicit CSqlQuery(const char* query, CSqlDataBase *db);
	explicit CSqlQuery(CSqlDataBase *db);
	CSqlQuery(const CSqlQuery& other);
	CSqlQuery& operator=(const CSqlQuery& other);
	~CSqlQuery();

	// �رղ�ѯ�����е�����(һ�㲻�õ��ã�ֱ�ӵȴ����������������,��Ҫ�����Sqlite���ܹ������رյ�����)
	bool Close();

	// �жϽ�����Ƿ�Ϊ��,��Ϊ��-true
	bool isValid() const;
	// ��ѯ�Ƿ�ɹ�,�ɹ�-true
	bool isActive() const;
	// �Ƿ��ѯ�ɹ�
	bool isSelect() const;

	// ��ȡ��ѯ��SQL���
	string lastQuery() const;

	// ��ȡ��ѯ�����������
	int GetRowNum() const;

	// ��ѯ����
	bool Query(const char* query);
	bool QueryBinary(const char* query);
	bool Query();
		
	//����ս����
	void clear();

	// �ж�ĳ���ֶ������Ƿ�Ϊ��
	bool isFieldNull(int field) const;

	// ��ȡ�ֶζ��峤��
	int GetFieldDefineSize(const char*szFldName);
	int GetFieldDefineSize(int nFldIndex);

	// ��ȡ�ֶ���Ŀ
	int GetFieldNum();

	// �����ֶ�index��ȡname
	string GetFieldName(int i);

	// ��ȡ�ֶ�����
	int GetFieldType(const char*szFldName);
	int GetFieldType(int nFldIndex);

	// �ƶ��й��
	void MoveFirst();					
	void MoveNext() ;			
	void MovePrevious();
	void MoveLast();

	// �й���Ƿ���ĩβ/��ʼ
	bool IsEOF();
	bool IsBOF();

	// ��ѯ�����Ϊ��/NULL
	bool IsEmpty();
	bool IsNull();

	// ȡ����
	bool GetValue(int nColumns, bool& bValue, bool &nIsNull );
	bool GetValue(char* strFieldName, bool& bValue, bool &nIsNull );

	bool GetValue(int nColumns, byte& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, byte& nValue, bool &nIsNull );

	bool GetValue(int nColumns, short& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, short& nValue, bool &nIsNull );

	bool GetValue(int nColumns, int& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, int& nValue, bool &nIsNull );

	bool GetValue(int nColumns, long& lValue, bool &nIsNull );
	bool GetValue(char* strFieldName, long& lValue, bool &nIsNull );

	bool GetValue(int nColumns, __int64& lValue, bool &nIsNull );
	bool GetValue(char* strFieldName, __int64& lValue, bool &nIsNull );

	bool GetValue(int nColumns, float& fValue, bool &nIsNull );
	bool GetValue(char* strFieldName, float& fValue, bool &nIsNull);

	bool GetValue(int nColumns, double& lValue, bool &nIsNull );
	bool GetValue(char* strFieldName, double& lValue, bool &nIsNull );

	bool GetValue(int nColumns, tm& time, bool &nIsNull );
	bool GetValue(char* strFieldName, tm& time, bool &nIsNull );

	bool GetValue(int nColumns, char* strValue, short len,bool &nIsNull);
	bool GetValue(char* strFldName, char* strValue, short len, bool &nIsNull);

	bool GetValue(int nColumns, string& strValue, bool &nIsNull);
	bool GetValue(char* strFieldName, string& strValue, bool &nIsNull);

	bool GetValue(int nColumns, byte** bDat, long *len, bool &nIsNull );
	bool GetValue(char* strFieldName, byte** bDat, long *len, bool &nIsNull );

private:
	friend void qInit(CSqlQuery *q, const char* query, CSqlDataBase *db);
	CSqlQuery(CSqlRecordset *r);
	const CSqlDriver* driver() const;


	inline void qAtomicAssign(CSqlQueryPrivate *&d, CSqlQueryPrivate *x);
	CSqlQueryPrivate* d;
};
