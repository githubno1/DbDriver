#pragma once

#include "SqlDriver.h"
#include "SqlRecordset.h"

#include "spatialite.h"
#pragma  comment(lib,"spatialite_i.lib")

class CSqliteDriverPrivate;
class CSqliteResultPrivate;
class CSqliteSQLDriver;

class CSqliteSQLResult: public CSqlRecordset
{
	friend class CSqliteResultPrivate;
	friend class CSqliteSQLDriver;

public:
	explicit CSqliteSQLResult(const CSqliteSQLDriver* db);
	~CSqliteSQLResult();

	//void virtual_hook(int id, void *data);

protected:
	void cleanup();
	bool fetch(int i);
	bool fetchFirst();
	bool fetchLast();

	bool IsFieldNull(int field);
	bool reset(const char* query, short execFormate);
	int size();
	int SelectRowCount();
	long lastInsertId() const;
	bool prepare(const string& query);
	bool exec();

	//ȡ�ֶθ���
	int GetFieldNum();
	//ȡ�ֶ���/�ֶα��
	string GetFieldName(long lIndex);		
	int GetIndex(const char* strFieldName);		

	int GetFieldType(int lIndex);
	int GetFieldType(const char* lpszFieldName);

	void MoveFirst();						
	void MoveNext();		
	void MovePrevious();	
	void MoveLast();	

	bool IsEOF();
	bool IsBOF();

	bool IsNull();
	bool IsEmpty();

	//��ȡ����ʵ�ʳ���
	int GetValueSize(long lIndex);				
	int GetValueSize(char* lpszFieldName);	
	//ȡ�ֶζ��峤��
	int GetFieldDefineSize(int lIndex);
	int GetFieldDefineSize(const char* lpszFieldName);

	bool GetValue(int nColumns, _variant_t& vt, bool &nIsNull );
	bool GetValue(char* strFieldName, _variant_t& vt, bool &nIsNull);

	bool GetValue(int nColumns, bool& bValue, bool &nIsNull );
	bool GetValue(char* strFieldName, bool& bValue, bool &nIsNull );

	bool GetValue(int nColumns, byte& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, byte& nValue, bool &nIsNull );

	bool GetValue(int nColumns, short& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, short& fValue, bool &nIsNull );

	bool GetValue(int nColumns, int& nValue, bool &nIsNull );
	bool GetValue(char* strFieldName, int& nValue, bool &nIsNull );

	bool GetValue(int nColumns, long& lValue, bool &nIsNull );
	bool GetValue(char* strFieldName, long& lValue, bool &nIsNull );

	bool GetValue(int nColumns, __int64& lValue, bool &nIsNull );
	bool GetValue(char* strFieldName, __int64& lValue, bool &nIsNull );

	bool GetValue(int nColumns, float& fValue, bool &nIsNull );
	bool GetValue(char* strFieldName, float& fValue, bool &nIsNull );

	bool GetValue(int nColumns, double& dValue, bool &nIsNull );
	bool GetValue(char* strFieldName, double& dValue, bool &nIsNull );

	bool GetValue(int nColumns, string& strValue, bool &nIsNull );
	bool GetValue(char* strFieldName, string& strValue, bool &nIsNull );

	bool GetValue(int nColumns, char* strValue, short len,bool &nIsNull);
	bool GetValue(char* strFldName, char* strValue, short len, bool &nIsNull);

	bool GetValue(int nColumns, tm& time, bool &nIsNull );
	bool GetValue(char* strFieldName, tm& time, bool &nIsNull );

	bool GetValue(int nColumns, byte** bDat, long *len, bool &nIsNull );
	bool GetValue(char* strFieldName, byte** bDat, long *len, bool &nIsNull );
private:
	inline void InitRowNum();
private:
	byte *m_blobData;
	CSqliteResultPrivate *d;
	long m_lCurrRow;
	long m_lAllSelectRow;
	long m_lFieldNum;

};

class  CSqliteSQLDriver :public CSqlDriver
{
	friend class CSqliteSQLResult;
public:
	CSqliteSQLDriver();
	CSqliteSQLDriver(sqlite3 *connection);
	~CSqliteSQLDriver();

	bool hasFeature(DriverFeature f) const	{return true;}
	
public:
	//�������ݿ�
	//db Ϊ���ݿ��ļ�ȫ·���������ļ�����
	bool open(const char* db, const char* user, const char* password,
		const char* host, int port, const char* connOpts);

	//�Ͽ����ݿ�����
	void close();

	//�Ƿ�����
	bool IsOpen();

	//���ݿ�æ���еȴ�����
	//ms:�ȴ��ĺ�����
	int BusyWait(int ms);
	
	// ����
	bool BeginTransaction();
	bool CommitTransaction();
	bool RollbackTransaction();

	//�ǲ�ѯ���
	int ExecuteSql(const char* strSql);
	int ExecBinary(const char* strSql, char** pParas,int *len, short nParamsNum);

	bool PutBlob(const char *strWhereSql, const char *szTableName, const char* szFldName, byte*szVal, long len)
	{
		return false;
	}

	int ExecuteSql(char**& strSql, long len, long lOptions);

	CSqlRecordset *createResult() const;

private:
	CSqliteDriverPrivate *d;

};
